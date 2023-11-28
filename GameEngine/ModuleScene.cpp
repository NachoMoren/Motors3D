#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    sceneObject = nullptr; 
    selectedObject = nullptr; 
    draggedObject = nullptr; 
    hoveredObject = nullptr; 
}

ModuleScene::~ModuleScene()
{
}

bool ModuleScene::Init()
{
    sceneObject = new GameObject(); 
    sceneObject->ChangeName("Scene");

    GameObject* dummy = new GameObject();
    dummy->ChangeName("Dummy");

    sceneObject->NewChild(dummy);

	return true;
}

update_status ModuleScene::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleScene::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	return true;
}

void ModuleScene::DrawTree(GameObject* go) {
    //Flags to open the hierarchy by default or by clicking the arrow
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;

    //In case there is no children, arrow won't appear
    if (go->mChildren.size() == 0) {
        flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
    }

    bool isNodeOpen = ImGui::TreeNodeEx(go, flags, go->_name.c_str());

    //Start drawing the ui
    if (ImGui::BeginDragDropSource()) {
        ImGui::SetDragDropPayload("Game Object", go, sizeof(GameObject*));
        draggedObject = go; 
        ImGui::Text("Drag");
        ImGui::EndDragDropSource();
    }

    if (ImGui::IsItemHovered()) {
        hoveredObject = go; 
        if(ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left)) {
            selectedObject = go;
        }
    }

    //
    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GameObject")) {
            //draggedObject->SetParent(hoveredObject); 
        }
        ImGui::EndDragDropTarget(); 
    }

    if (!go->mChildren.empty()) {
        for (uint i = 0; i < go->mChildren.size(); i++) {
            DrawTree(go->mChildren[i]);
        }
        ImGui::TreePop(); 
    }

}
