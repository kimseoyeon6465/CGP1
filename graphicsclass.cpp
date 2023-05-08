////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_ModelSky = 0;
	m_ModelMonkey = 0;
	m_ModelBird = 0;
	m_ModelDeer = 0;
	m_ModelPig = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_TextureShader = 0;

}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);	// for cube
//	m_Camera->SetPosition(0.0f, 0.5f, -3.0f);	// for chair

	// Create the model object.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	
	result = m_Model->Initialize(m_D3D->GetDevice(), L"./data/10446_Palm_Tree_v1_max2010_iteration-2.obj", L"./data/10446_Palm_Tree_v1_Diffuse.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_ModelSky = new ModelClass;
	if (!m_ModelSky)
	{
		return false;
	}
	result = m_ModelSky->InitializeOne(m_D3D->GetDevice(), L"./data/cube.obj", L"./data/AnyConv.com__e9082b7e9a3b6975b2f20756aaddf95b.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_ModelMonkey = new ModelClass;
	if (!m_ModelMonkey)
	{
		return false;
	}
	result = m_ModelMonkey->InitializeOne(m_D3D->GetDevice(), L"./data/12958_Spider_Monkey_v1_l2.obj", L"./data/12958_Spider_Monkey_diff.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_ModelBird = new ModelClass;
	if (!m_ModelBird)
	{
		return false;
	}

	// Initialize the model object.

	result = m_ModelBird->InitializeBird(m_D3D->GetDevice(), L"./data/12248_Bird_v1_L2.obj", L"./data/AnyConv.com__12248_Bird_v1_diff.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the model object.
	m_ModelDeer = new ModelClass;
	if (!m_ModelDeer)
	{
		return false;
	}

	// Initialize the model object.

	result = m_ModelDeer->InitializeDeer(m_D3D->GetDevice(), L"./data/deer.obj", L"./data/deertexture.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	//Pig
	m_ModelPig = new ModelClass;
	if (!m_ModelPig)
	{
		return false;
	}

	// Initialize the model object.

	result = m_ModelPig->InitializeOne(m_D3D->GetDevice(), L"./data/16433_Pig.obj", L"./data/AnyConv.com__24397251-texture-of-brown-pig-suede-background-macro.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_ModelFloor = new ModelClass;
	if (!m_ModelFloor)
	{
		return false;
	}

	// Initialize the model object.
	result = m_ModelFloor->InitializeFloor(m_D3D->GetDevice(), L"./data/sand0053.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
		//m_Light->SetAmbientColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	//	m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
	//	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	//	m_Light->SetDirection(1.0f, 0.0f, 0.0f);
	m_Light->SetDirection(1.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	return true;
}



void GraphicsClass::Shutdown()
{
	// Release the model object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}
	if (m_ModelSky)
	{
		m_ModelSky->Shutdown();
		delete m_ModelSky;
		m_ModelSky = 0;
	}

	if (m_ModelMonkey)
	{
		m_ModelMonkey->Shutdown();
		delete m_ModelMonkey;
		m_ModelMonkey = 0;
	}

	if (m_ModelBird)
	{
		m_ModelBird->Shutdown();
		delete m_ModelBird;
		m_ModelBird = 0;
	}

	if (m_ModelDeer)
	{
		m_ModelDeer->Shutdown();
		delete m_ModelDeer;
		m_ModelDeer = 0;
	}

	if (m_ModelPig)
	{
		m_ModelPig->Shutdown();
		delete m_ModelPig;
		m_ModelPig = 0;
	}

	if (m_ModelFloor)
	{
		m_ModelFloor->Shutdown();
		delete m_ModelFloor;
		m_ModelFloor = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	return;
}

bool GraphicsClass::Frame()
{
	bool result;

	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}

void GraphicsClass::OnAmbient()
{
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
}

void GraphicsClass::OnDiffuse()
{
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void GraphicsClass::OnSpecular()
{
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);
}

void GraphicsClass::OffAmbient()
{
	m_Light->SetAmbientColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void GraphicsClass::OffDiffuse()
{
	m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void GraphicsClass::OffSpecular()
{
	m_Light->SetSpecularColor(0.0f, 0.0f, 0.0f, 0.0f);
	m_Light->SetSpecularPower(0.0f);
}

CameraClass* GraphicsClass::GetCamera()
{
	return m_Camera;
}


bool GraphicsClass::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, scalingMatrix, translationMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	//worldMatrix = XMMatrixRotationY(rotation);
	//scalingMatrix = XMMatrixScaling(500.0f, 500.0f, 500.0f);
	//scalingMatrix = XMMatrixScaling(50.0f, 50.0f, 50.0f);
	//scalingMatrix = XMMatrixScaling(5.0f, 5.0f, 5.0f);
	//scalingMatrix = XMMatrixScaling(0.5f, 0.5f, 0.5f);
	//scalingMatrix = XMMatrixScaling(0.05f, 0.05f, 0.05f);
	//scalingMatrix = XMMatrixScaling(0.005f, 0.005f, 0.005f);
	//scalingMatrix = XMMatrixScaling(0.001f, 0.001f, 0.001f);

	scalingMatrix = XMMatrixScaling(0.002f,0.002f, 0.002f);
	translationMatrix = XMMatrixTranslation(0.0f, -0.0f, 0.0f);

	worldMatrix = worldMatrix * scalingMatrix*translationMatrix;

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetVertexCount(), m_Model->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	scalingMatrix = XMMatrixScaling(200.0f, 200.0f, 2.0f);
	translationMatrix = XMMatrixTranslation(0.0f, 0.0f, 50.0f);

	worldMatrix = worldMatrix * scalingMatrix * translationMatrix;
	//worldMatrix = XMMatrixRotationY(rotation);


	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ModelSky->Render(m_D3D->GetDeviceContext());

	//// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_ModelSky->GetVertexCount(), m_ModelSky->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_ModelSky->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}
	//Monkey
	//scalingMatrix = XMMatrixScaling(0.002f, 0.002f, 0.002f);
	//scalingMatrix = XMMatrixScaling(5.0f, 5.0f, 5.0f);

	//scalingMatrix = XMMatrixScaling(500.0f, 500.0f, 500.0f);
	//scalingMatrix = XMMatrixScaling(50.0f, 50.0f, 50.0f);
	//scalingMatrix = XMMatrixScaling(5.0f, 5.0f, 5.0f);
	//scalingMatrix = XMMatrixScaling(0.5f, 0.5f, 0.5f);
	//scalingMatrix = XMMatrixScaling(0.05f, 0.05f, 0.05f);
	//scalingMatrix = XMMatrixScaling(0.005f, 0.005f, 0.005f);
	//scalingMatrix = XMMatrixScaling(0.001f, 0.001f, 0.001f);
	//scalingMatrix = XMMatrixScaling(0.0005f, 0.0005f, 0.0005f);
	scalingMatrix = XMMatrixScaling(0.00005f, 0.00005f, 0.00005f);
	// 
	//scalingMatrix = XMMatrixScaling(0.000002f, 0.000002f, 0.000002f);

	translationMatrix = XMMatrixTranslation(0.0f, -1.0f, -2.0f);

	worldMatrix = worldMatrix * scalingMatrix * translationMatrix;
	//worldMatrix = XMMatrixRotationY(rotation);


	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ModelMonkey->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_ModelMonkey->GetVertexCount(), m_ModelMonkey->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_ModelMonkey->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}
	//scalingMatrix = XMMatrixScaling(5.0f, 5.0f, 5.0f);
	//scalingMatrix = XMMatrixScaling(5.0f, 5.0f, 5.0f);
	//scalingMatrix = XMMatrixScaling(0.5f, 0.5f, 0.5f);
	//scalingMatrix = XMMatrixScaling(0.005f, 0.005f, 0.005f);
	//scalingMatrix = XMMatrixScaling(0.001f, 0.001f, 0.001f);
	//scalingMatrix = XMMatrixScaling(0.05f, 0.05f, 0.05f);

	//scalingMatrix = XMMatrixScaling(0.000002f, 0.000002f, 0.000002f);

	//Bird
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	//scalingMatrix = XMMatrixScaling(0.002f, 0.002f, 0.002f);
	scalingMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);

	translationMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	worldMatrix = worldMatrix * scalingMatrix * translationMatrix;

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ModelBird->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_ModelBird->GetVertexCount(), m_ModelBird->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_ModelBird->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	// Deer
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	//scalingMatrix = XMMatrixScaling(5.0f, 5.0f, 5.0f);
	//scalingMatrix = XMMatrixScaling(0.5f, 0.5f, 0.5f);
	//scalingMatrix = XMMatrixScaling(0.05f, 0.05f, 0.05f);
	//scalingMatrix = XMMatrixScaling(0.005f, 0.005f, 0.005f);
	//scalingMatrix = XMMatrixScaling(0.001f, 0.001f, 0.001f);
	//scalingMatrix = XMMatrixScaling(0.00005f, 0.00005f, 0.00005f);
	//scalingMatrix = XMMatrixScaling(0.5f, 0.5f, 0.5f);
	//scalingMatrix = XMMatrixScaling(5.0f, 5.0f, 5.0f);
	scalingMatrix = XMMatrixScaling(0.001f, 0.001f, 0.001f);


	//scalingMatrix = XMMatrixScaling(0.000002f, 0.000002f, 0.000002f);
	translationMatrix = XMMatrixTranslation(-1.0f, -1.0f, 0.0f);

	worldMatrix = worldMatrix * scalingMatrix * translationMatrix;

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ModelDeer->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_ModelDeer->GetVertexCount(), m_ModelDeer->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_ModelDeer->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}


	scalingMatrix = XMMatrixScaling(0.00005f, 0.00005f, 0.00005f);
	// 
	//scalingMatrix = XMMatrixScaling(0.000002f, 0.000002f, 0.000002f);

	translationMatrix = XMMatrixTranslation(0.0f, -1.0f, -2.0f);


	worldMatrix = worldMatrix * scalingMatrix * translationMatrix;
	//worldMatrix = XMMatrixRotationY(rotation);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ModelMonkey->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_ModelMonkey->GetVertexCount(), m_ModelMonkey->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_ModelMonkey->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}


	// Pig
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	worldMatrix = XMMatrixRotationY(rotation);

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	//worldMatrix = XMMatrixRotationY(rotation);
	//scalingMatrix = XMMatrixScaling(500.0f, 500.0f, 500.0f);
	//scalingMatrix = XMMatrixScaling(50.0f, 50.0f, 50.0f);
	//scalingMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	scalingMatrix = XMMatrixScaling(0.8f, 0.8f, 0.8f);
	//scalingMatrix = XMMatrixScaling(0.05f, 0.05f, 0.05f);
	//scalingMatrix = XMMatrixScaling(0.005f, 0.005f, 0.005f);
	//scalingMatrix = XMMatrixScaling(0.001f, 0.001f, 0.001f);

	//scalingMatrix = XMMatrixScaling(0.002f, 0.002f, 0.002f);
	translationMatrix = XMMatrixTranslation(-0.25f, -1.0f, -2.0f);

	worldMatrix = worldMatrix * scalingMatrix * translationMatrix;

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ModelPig->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_ModelPig->GetVertexCount(), m_ModelPig->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_ModelPig->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	worldMatrix = XMMatrixRotationX(20.0f);
	translationMatrix = XMMatrixTranslation(0.0f, -2.0f, 0.0f);
	//worldMatrix = XMMatrixRotationX(45.0f);
	scalingMatrix = XMMatrixScaling(10.0f, 2.0f, 10.0f);


	worldMatrix = worldMatrix*scalingMatrix* translationMatrix;

	m_ModelFloor->Render(m_D3D->GetDeviceContext());


	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_ModelFloor->GetVertexCount(), m_ModelFloor->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_ModelFloor->GetTexture());
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}