#include "Assignment0Layer.h"

#include <vector>

#include <GL/glew.h>
#include <imgui.h>

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/gtx/string_cast.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Utils.h"

void Assignment0Layer::onAttach()
{

	m_shader = new Shader("res/shaders/mit/assignment0_vs.glsl", "res/shaders/mit/assignment0_fs.glsl");
	loadModel(m_filepath);

	glEnable(GL_DEPTH_TEST);

	m_projection = glm::perspective(glm::radians(90.0f), 16.0f / 9.0f, 0.1f, 100.f);
	m_cameraPosition = glm::vec3(0.0f, -2.0f, -20.0f);
	m_lightDirection = glm::vec3(0.0f, -1.0f, -0.5f);
	
	m_color = glm::vec3(0.2f, 0.3f, 0.8f);
	
	
}

void Assignment0Layer::onUpdate(float deltatime)
{

	if (m_rotation) {
		m_rotationAngle += deltatime * 10;
	}

	glClearColor(0.2, 0.2, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader->bind();
	
	glm::mat4 view = glm::rotate(glm::translate(glm::mat4(1.0f), m_cameraPosition), glm::radians(0.0f), glm::vec3(1, 0, 0));
	glm::mat4 model = glm::rotate(glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(1)), glm::vec3(0, 0, 0)), glm::radians(m_rotationAngle), glm::vec3(0, 1, 0));
	
	glm::mat4 MVP = m_projection * view * model;


	m_shader->setUniform("MVP", MVP);
	m_shader->setUniform("model", model);
	m_shader->setUniform("color", m_color);

	m_shader->setUniform("lightDirection", m_lightDirection);
	

	glBindVertexArray(m_vao);
	checkOpenGLError("Errors After bind: ");
	glDrawElements(GL_TRIANGLES, m_count, GL_UNSIGNED_INT, (GLvoid*)0);
	checkOpenGLError("Errors after draw: ");
}

void Assignment0Layer::onDetach()
{
}

void Assignment0Layer::onImGuiRender()
{
	ImGui::Begin("Assingment 0 - OpenGL MEsh Viewer");

	ImGui::Text("Object Props");
	ImGui::InputText("Filepath", &m_filepath[0], IM_ARRAYSIZE(m_filepath));

	if (ImGui::Button("Load!"))
	{
		loadModel(m_filepath);
	}
	
	ImGui::ColorEdit3("Main Color", (float*)&m_color);
	ImGui::Checkbox("Rotating", &m_rotation);

	ImGui::Separator();

	ImGui::Text("World Props");
	ImGui::DragFloat3("Camera Position", (float*)&m_cameraPosition, 0.1f);
	ImGui::DragFloat3("Light Direction", (float*)&m_lightDirection, 0.1f);

	ImGui::End();
}

void Assignment0Layer::loadModel(const char * filepath)
{
	LOG("Filepath: " << filepath);

	// Read file via ASSIMP
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	// Check for errors
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	LOG("MODEL LOADED: " << scene->mNumMeshes << " meshes found");

	//SUPPORTING ONE MESH
	aiMesh * mesh = scene->mMeshes[0];

	LOG("NUM OF VERTICES: " << mesh->mNumVertices);

	std::vector<glm::vec3> positions;
	//std::vector<glm::vec2> textureCoords;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;


	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		positions.push_back(glm::vec3(
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		));

		// Normals
		normals.push_back(glm::vec3(
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			mesh->mNormals[i].z
		));
		/*
		// Texture Coordinates
		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			textureCoords.push_back(
				glm::vec2(mesh->mTextureCoords[0][i].x,
					mesh->mTextureCoords[0][i].y
				));

		}
		else
		{
			textureCoords.push_back(
				glm::vec2(0, 0));
		}
		*/
	}

	// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// Retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	GLuint vbPositions;
	glGenBuffers(1, &vbPositions);
	glBindBuffer(GL_ARRAY_BUFFER, vbPositions);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), std::data(positions), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


	GLuint vbNormals;
	glGenBuffers(1, &vbNormals);
	glBindBuffer(GL_ARRAY_BUFFER, vbNormals);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), std::data(normals), GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	unsigned int modelIndices;
	glGenBuffers(1, &modelIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), std::data(indices), GL_STATIC_DRAW);

	m_count = (int)indices.size();

	checkOpenGLError("Errors on Model Loader: ");
}
