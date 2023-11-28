#include "Application.h"
#include "ModuleEditor.h"

#include "ModuleWindow.h"
#include "Globals.h"
#include "Assimp/include/version.h"
#include "GameObject.h"


#include "ImGui/imgui.h"
#include "ImGui//backends/imgui_impl_sdl2.h"
#include "ImGui//backends/imgui_impl_opengl3.h"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigDockingWithShift = false; //Can move UI without pressing shift

    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
    ImGui_ImplOpenGL3_Init();

    isWireframe = false; 
    showConfig = true; 
    showConsole = true; 
    showAbout = false; 
    showHierarchy = false; 

    cubePath = "../Assets/Basic_Shapes/Cube.fbx";
    conePath = "../Assets/Basic_Shapes/Cone.fbx";
    spherePath = "../Assets/Basic_Shapes/Sphere.fbx";
    cylinderPath = "../Assets/Basic_Shapes/Cylinder.fbx";

    SDL_GetVersion(&version);

	return true;
}

bool ModuleEditor::DrawEditor()
{
   
    bool ret = true;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    //Docking Stuff
    ImGuiIO& io = ImGui::GetIO();
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_MenuBar;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::SetNextWindowBgAlpha(0.0f);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    if (ImGui::Begin("DockSpace Demo", nullptr, windowFlags)) {
        ImGui::PopStyleVar(3);

        ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        ImGui::End();
    }
    
    
    // Demo Menu
    //ImGui::ShowDemoWindow();

    // MainMenuBar
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Import")) {}
            if (ImGui::MenuItem("Close", "Ctrl+Q")) { ret = false; } // <-- Exit Code
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Window"))
        {
            if (ImGui::MenuItem("Config")) { 
                showConfig = !showConfig; 
            }
            if (ImGui::MenuItem("Console")) {
                showConsole = !showConsole;
            }
            if (ImGui::MenuItem("Hierarchy")) {
                showHierarchy = !showHierarchy;
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Select"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if(ImGui::MenuItem("Documentation"))
                ShellExecute(0, 0, "https://github.com/NachoMoren/Scaffold", 0, 0, SW_SHOW);
            if (ImGui::MenuItem("About"))
                showAbout = !showAbout; 
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
    else {
        ImGui::End();
    }
    
    // Console Window
    if(showConsole)
        ConsoleWindow(); 

    //Config
    if(showConfig)
        Configuration();

    if (showAbout)
        About(); 

    if (showHierarchy)
        Hierarchy();
    
    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return ret;
}

bool ModuleEditor::CleanUp()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

	return true;
}

void ModuleEditor::AddFPS(const float aFPS)
{
    if (mFPSLog.size() >= mFPSLogSize) {
        mFPSLog.erase(mFPSLog.begin());

    }
   
    mFPSLog.push_back(aFPS);
   

}

void ModuleEditor::AddLog(const std::string& str)
{
    ImGui::Text(str.data());
}

void ModuleEditor::ConsoleWindow()
{
    if (ImGui::Begin("Console")) {
        AddLog(getLog());

        ImGui::End();
    }
    else {
        ImGui::End();
    }
}

void ModuleEditor::About() {
    if (ImGui::Begin("About")) {
        std::string ver; 
        ImGui::Text("Scaffold Engine");
        ImGui::Separator();
        ImGui::TextDisabled("By Nacho Moreno and Biel Rubio\n");
        ImGui::Text("A new engine made by two CITM students, for educational purpose.");
        ImGui::Text("\n3rd Party libraries: \n");
        ImGui::Separator();
        ImGui::Text(" - SDL v%d.%d.%d", version.major, version.minor, version.patch);

        ver = " - ImGui v"  + std::string(ImGui::GetVersion());
        ImGui::Text(ver.c_str());

        ver = " - Assimp v" + std::to_string(aiGetVersionMajor()) + '.' + std::to_string(aiGetVersionMinor()) + '.' + std::to_string(aiGetVersionRevision());
        ImGui::Text(ver.c_str());

        ver = " - DevIL v1.8.0"; // No real time version available
        ImGui::Text(ver.c_str());

        ver = " - OpenGL v";
        ver += (const char*)glGetString(GL_VERSION);
        ImGui::Text(ver.c_str());

        ver = " - Glew v";
        ver += (const char*)glewGetString(GLEW_VERSION);
        ImGui::Text(ver.c_str());
        
        ImGui::Text(" - Parson v1.5.3"); //No real time version available

        ImGui::Text(" - MathGeoLib v1.5"); //No real time available

        
        ImGui::Text("\nLicense: ");
        ImGui::Separator();
        ImGui::Text("\nMIT License");
        ImGui::Text("\nCopyright (c) 2023 NachoMoren");
        ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy \nof this software and associated documentation files (the 'Software'), to deal \nin the Software without restriction, including without limitation the rights \nto use, copy, modify, merge, publish, distribute, sublicense, and/or sell \ncopies of the Software, and to permit persons to whom the Software is \nfurnished to do so, subject to the following conditions:");
        ImGui::Text("\nThe above copyright notice and this permission notice shall be included in all \ncopies or substantial portions of the Software.");
        ImGui::Text("\nTHE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR \nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, \nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE \nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER \nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, \nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE \nSOFTWARE.");

        ImGui::End();
    }
    else {
        ImGui::End();
    }
}
void ModuleEditor::Hierarchy() {
    if (ImGui::Begin("Hierarchy")) {
        ImGui::End();
    }
    else {
        ImGui::End();
    }
}

void ModuleEditor::Configuration()
{

    if (ImGui::Begin("Configuration")) {

        if (ImGui::CollapsingHeader("Application")) {

            ImGui::NewLine();
            ImGui::PlotHistogram("FPS", mFPSLog.data(), mFPSLogSize);
            ImGui::DragInt("Graph size", &mFPSLogSize, 0.5f, 1, 100);
            ImGui::NewLine();

        }
        if (ImGui::CollapsingHeader("LevelManager")) {

            ImGui::NewLine();
        }
        if (ImGui::CollapsingHeader("Window")) {

            ImGui::NewLine();
            if (ImGui::DragInt("Width", &App->window->width)) {
                App->window->UpdateSize();
            }
            if (ImGui::DragInt("Height", &App->window->height)) {
                App->window->UpdateSize();
            }
            if (ImGui::Checkbox("FullScreen", &App->window->isFullscreen)) {
                if(App->window->isFullscreen)
                    SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_FULLSCREEN);
                else
                    SDL_SetWindowFullscreen(App->window->window, 0);
            }
            if (ImGui::Checkbox("Resizable", &App->window->isResizable)) {
                if (App->window->isResizable)
                    SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_RESIZABLE);
                else
                    SDL_SetWindowFullscreen(App->window->window, 0);
            }
            if (ImGui::Checkbox("Borderless", &App->window->isBorderless)) {
                if(App->window->isBorderless)
                    SDL_SetWindowBordered(App->window->window, SDL_FALSE);
                else
                    SDL_SetWindowBordered(App->window->window, SDL_TRUE);
            }
            if (ImGui::Checkbox("FullDesktop", &App->window->IsFullDesktop)) {
                if(App->window->IsFullDesktop)
                    SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                else
                    SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_RESIZABLE);
            }
            ImGui::NewLine();
        }
        if (ImGui::CollapsingHeader("Renderer")) {
            ImGui::Checkbox("Cube Checkers", &App->renderer3D->drawCube);
            ImGui::Checkbox("Wireframe", &isWireframe);
            if (ImGui::CollapsingHeader("Basic Shapes")) {
                if (ImGui::Button("Cube"))
                    App->meshRenderer->LoadMesh(cubePath);
                if (ImGui::Button("Sphere"))
                    App->meshRenderer->LoadMesh(spherePath);
                if (ImGui::Button("Cone"))
                    App->meshRenderer->LoadMesh(conePath);
                if (ImGui::Button("Cylinder"))
                    App->meshRenderer->LoadMesh(cylinderPath);
            }
        }
        if (ImGui::CollapsingHeader("Camera")) {

            ImGui::NewLine();
        }
        if (ImGui::CollapsingHeader("Textures")) {

            ImGui::NewLine();
        }
        if (ImGui::CollapsingHeader("Audio")) {

            ImGui::NewLine();
        }
        if (ImGui::CollapsingHeader("Physics")) {
            
            ImGui::NewLine();
        }
        if (ImGui::CollapsingHeader("FileSystem")) {

            ImGui::NewLine();
        }
        if (ImGui::CollapsingHeader("Hardware/Software status")) {
            ImGui::Text("SDL Version:");
            ImGui::SameLine(); 
            ImGui::TextColored(ColToImVec(Green), "%d.%d.%d", version.major, version.minor, version.patch);

            ImGui::Separator();

            ImGui::Text("CPU's: ");
            ImGui::SameLine();
            ImGui::TextColored(ColToImVec(Green), "%d", SDL_GetCPUCount());

            ImGui::Text("System RAM: ");
            ImGui::SameLine();
            ImGui::TextColored(ColToImVec(Green), " %d Gb", SDL_GetSystemRAM());
            ImGui::Separator();

            ImGui::Text("System Data: ");
            ImGui::SameLine();
            ImGui::TextColored(ColToImVec(Green), "%s", GetSystemData());
            ImGui::Separator();

            ImGui::Text("GPU: ");
            ImGui::SameLine();
            ImGui::TextColored(ColToImVec(Green), "%s", glGetString(GL_RENDERER));

            ImGui::Text("Brand: ");
            ImGui::SameLine();
            ImGui::TextColored(ColToImVec(Green), "%s", glGetString(GL_VENDOR));

            ImGui::Text("Version: ");
            ImGui::SameLine();
            ImGui::TextColored(ColToImVec(Green), "%s", glGetString(GL_VERSION));

            ImGui::Text("VRAM Budget:");
            ImGui::SameLine();
            ImGui::TextColored(ColToImVec(Green), "%i Mb", GetBudget());

            ImGui::Text("VRAM Usage:");
            ImGui::SameLine();
            ImGui::TextColored(ColToImVec(Green), "%i Mb", GetUsage());

            ImGui::Text("VRAM Available:");
            ImGui::SameLine();
            ImGui::TextColored(ColToImVec(Green), "%i Mb", GetAvailable());

            ImGui::Text("VRAM Reserved:");
            ImGui::SameLine();
            ImGui::TextColored(ColToImVec(Green), "%i Mb", GetReserved());

        }

        ImGui::End();
    }
    else {
        ImGui::End();
    }

}

ImVec4 ModuleEditor::ColToImVec(const Color& color) {
    return ImVec4(color.r, color.g, color.b, color.a);
}

const char* ModuleEditor::GetSystemData() {
    systemData.clear();
    if (SDL_Has3DNow())
    {
        systemData.append("3D Now, ");
    }

    if (SDL_HasAVX())
    {
        systemData.append("AVX, ");
    }

    if (SDL_HasAVX2())
    {
        systemData.append("AVX2, ");
    }

    if (SDL_HasAltiVec())
    {
        systemData.append("AltiVec, ");
    }

    if (SDL_HasMMX())
    {
        systemData.append("MMX, ");
    }

    if (SDL_HasRDTSC())
    {
        systemData.append("RDTSC, ");
    }

    if (SDL_HasSSE())
    {
        systemData.append("SSE, ");
    }

    if (SDL_HasSSE2())
    {
        systemData.append("SSE2, ");
    }

    if (SDL_HasSSE3())
    {
        systemData.append("SSE3, ");
    }

    if (SDL_HasSSE41())
    {
        systemData.append("SSE41, ");
    }

    if (SDL_HasSSE41())
    {
        systemData.append("SSE42");
    }

    return systemData.data();
}

int ModuleEditor::GetUsage() {
    int usage;
    glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &usage);
    return usage / 1024.0f;
}

int ModuleEditor::GetAvailable() {
    int available;
    glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &available);
    return available / 1024.0f;
}

int ModuleEditor::GetBudget() {
    int budget;
    glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &budget);
    return budget / 1024.0f;
}

int ModuleEditor::GetReserved() {
    int reserved;
    glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX, &reserved);
    return reserved / 1024.0f;
}



