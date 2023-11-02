#include "Application.h"
#include "ModuleEditor.h"

#include "ModuleWindow.h"
#include "Globals.h"


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

	return true;
}

bool ModuleEditor::DrawEditor()
{
   
    bool ret = true;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

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
        if (ImGui::BeginMenu("Select"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About")) { ImGui::Text("We lit"); }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
    else {
        ImGui::End();
    }

    // Console Window
    if (ImGui::Begin("Console")) {
        AddLog(getLog());
       
        ImGui::End();
    }
    else {
        ImGui::End();
    }

    //Config
    Configuration();
    
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
            ImGui::NewLine();
            ImGui::Checkbox("Cube", &App->renderer3D->drawCube);
            ImGui::Checkbox("Wireframe", &isWireframe);
            ImGui::NewLine();
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

