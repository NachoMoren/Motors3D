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

    GameObject* dummy2 = new GameObject();
    dummy2->ChangeName("Dummy2");

    sceneObject->NewChild(dummy);

    sceneObject->NewChild(dummy2);

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
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;

    //In case there is no children, arrow won't appear
    if (go->mChildren.size() == 0) {
        flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
    }
    if (go->mParent == nullptr)
    {
        flags |= ImGuiTreeNodeFlags_DefaultOpen;
    }
    else
    {
        flags |= ImGuiTreeNodeFlags_OpenOnArrow;
    }

    //Mark which object the user picked
    if (go == selectedObject)
    {
        flags |= ImGuiTreeNodeFlags_Selected;
    }

    bool isNodeOpen = ImGui::TreeNodeEx(go, flags, go->_name.c_str());

    if (go->mChildren.size() == 0) {
        flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        isNodeOpen = false;
    }
    //Start drawing the ui
    if (ImGui::BeginDragDropSource()) {
        ImGui::SetDragDropPayload("Game Object", go, sizeof(GameObject*));
        draggedObject = go;
        ImGui::Text("Reparent");
        ImGui::EndDragDropSource();
    }

    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem)) {
        hoveredObject = go;
        if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left)) {
            selectedObject = go;
        }
    }

    if (ImGui::BeginDragDropTarget()) {
        ImGuiDragDropFlags dropFlags = ImGuiDragDropFlags_AcceptBeforeDelivery;
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Game Object")) {
            draggedObject->Reparent(hoveredObject);
        }
        ImGui::EndDragDropTarget();
    }

    if (ImGui::BeginPopupContextItem()) {
        if (ImGui::Button("Add empty child")) {
            go->NewChild(new GameObject("Child"));
            ImGui::CloseCurrentPopup();
        } 
        else if (ImGui::Button("Delete")) {
            //care with scene
            go->mParent->RemoveChild(go);
        }
        ImGui::EndPopup();
    }

    if (isNodeOpen) {
        if (!go->mChildren.empty()) {
            for (uint i = 0; i < go->mChildren.size(); i++) {
                DrawTree(go->mChildren[i]);
            }
            ImGui::TreePop();
        }
    }
}
