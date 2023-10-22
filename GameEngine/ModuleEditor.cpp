#include "Application.h"
#include "ModuleEditor.h"

#include "ModuleWindow.h"

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

	return true;
}

bool ModuleEditor::DrawEditor()
{
   
    bool ret = true;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // Demo Menu
    ImGui::ShowDemoWindow();

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

    // Console Window
    if (ImGui::Begin("Console")) {
        AddLog();
        for (int i = 0; i < mConsoleLog.size(); i++) {
            ImGui::Text(mConsoleLog[i]);

        }
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

void ModuleEditor::AddLog()
{
    if (mConsoleLog.size() >= 100) {
        mConsoleLog.erase(mConsoleLog.begin());

    }
    mConsoleLog = GET_LOG();
    //mConsoleLog.push_back(tmp_string);
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

            }
            if (ImGui::Checkbox("Resizable", &App->window->isResizable)) {

            }
            if (ImGui::Checkbox("Borderless", &App->window->isBorderless)) {

            }
            if (ImGui::Checkbox("FullDesktop", &App->window->IsFullDesktop)) {

            }
            ImGui::NewLine();
        }
        if (ImGui::CollapsingHeader("Renderer")) {

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

        ImGui::End();
    }

}
