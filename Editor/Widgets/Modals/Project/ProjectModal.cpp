/* ======================================================================== */
/*!
 * \file            ProjectModal.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The window that lets the user either create a new project or open an
   existing one.
 */
 /* ======================================================================== */

#include "ProjectModal.hpp"
#include <Editor.hpp>

#include "nfd.h"
#include <filesystem>
#include <fstream>

#include <Entry/Entry.hpp>

namespace Barrage
{
  void ProjectModal::Use(const char* strId)
  {
    if (!ImGui::BeginPopupModal(strId, NULL, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
    {
      return;
    }

    if (ImGui::Button("New project", ImVec2(120.0f, 0.0f)))
    {
      if (CreateNewProject())
      {
        ImGui::CloseCurrentPopup();
      }
    }

    ImGui::SetItemDefaultFocus();

    if (ImGui::Button("Open project", ImVec2(120.0f, 0.0f)))
    {
      if (OpenProject())
      {
        ImGui::CloseCurrentPopup();
      }
    }

    ImGui::EndPopup();
  }

  bool ProjectModal::CreateNewProject()
  {
    nfdchar_t* raw_path = NULL;
    nfdresult_t result = NFD_PickFolder(NULL, &raw_path);

    if (result != NFD_OKAY)
    {
      LogWidget::AddEntry("Could not create new project. (Problem selecting output folder.)");
      return false;
    }

    std::string project_folder_path(raw_path);
    free(raw_path);

    std::string project_name("Project");
    project_folder_path += "\\" + project_name;

    if (std::filesystem::exists(project_folder_path))
    {
      LogWidget::AddEntry("Could not create new project. (Project folder already exists.)");
      return false;
    }

    std::filesystem::create_directory(project_folder_path);
    std::ofstream project_file(project_folder_path + "/" + project_name + ".proj");

    if (project_file.is_open())
    {
      project_file.close();
    }
    else
    {
      LogWidget::AddEntry("Could not create new project. (Problem creating project file.)");
      std::filesystem::remove_all(project_folder_path);
      return false;
    }

    if (!std::filesystem::create_directory(project_folder_path + "/Assets"))
    {
      LogWidget::AddEntry("Could not create new project. (Could not create Assets folder.)");
      std::filesystem::remove_all(project_folder_path);
      return false;
    }

    if (!std::filesystem::create_directory(project_folder_path + "/Assets/Scenes"))
    {
      LogWidget::AddEntry("Could not create new project. (Could not create Scenes folder.)");
      std::filesystem::remove_all(project_folder_path);
      return false;
    }

    if (!std::filesystem::create_directory(project_folder_path + "/Assets/Shaders"))
    {
      LogWidget::AddEntry("Could not create new project. (Could not create Shaders folder.)");
      std::filesystem::remove_all(project_folder_path);
      return false;
    }

    if (!std::filesystem::create_directory(project_folder_path + "/Assets/Textures"))
    {
      LogWidget::AddEntry("Could not create new project. (Could not create Textures folder.)");
      std::filesystem::remove_all(project_folder_path);
      return false;
    }

    Entry entryFile;

    entryFile.AddSpace(Entry::SpaceEntry("Untitled", "Untitled"));

    if (!Entry::SaveToFile(entryFile, project_folder_path + "/Assets/entry.json"))
    {
      LogWidget::AddEntry("Could not create new project. (Could not create entry file.)");
      std::filesystem::remove_all(project_folder_path);
      return false;
    }

    Scene untitled_scene("Untitled");

    if (!Scene::SaveToFile(&untitled_scene, project_folder_path + "/Assets/Scenes/Untitled.scene"))
    {
      LogWidget::AddEntry("Could not create new project. (Could not create first scene.)");
      std::filesystem::remove_all(project_folder_path);
      return false;
    }

    /*if (!OpenProjectInternal(project_folder_path))
    {
      LogWidget::AddEntry("Could not create new project. (Could not open project after creation.)");
      std::filesystem::remove_all(project_folder_path);
      return false;
    }*/

    LogWidget::AddEntry(std::string("\"" + project_name + "\" project created in \"" + project_folder_path + "\"."));

    return true;
  }

  bool ProjectModal::OpenProject()
  {
    nfdchar_t* raw_path = NULL;
    nfdresult_t result = NFD_OpenDialog(NULL, NULL, &raw_path);

    if (result != NFD_OKAY)
    {
      LogWidget::AddEntry("Could not open project. (Problem selecting project file.)");
      return false;
    }

    std::string file_path(raw_path);
    free(raw_path);

    size_t lastSlashPos = file_path.find_last_of('/');
    file_path = file_path.substr(0, lastSlashPos);

    return OpenProjectInternal(file_path);
  }

  bool ProjectModal::OpenProjectInternal(std::string projectDirectory)
  {
    if (!std::filesystem::exists(projectDirectory + "/Assets"))
    {
      LogWidget::AddEntry("Could not open project. (No \"Assets\" folder.)");
      return false;
    }

    if (!std::filesystem::exists(projectDirectory + "/Assets/Scenes"))
    {
      LogWidget::AddEntry("Could not open project. (No \"Scenes\" folder.)");
      return false;
    }

    if (!std::filesystem::exists(projectDirectory + "/Assets/Shaders"))
    {
      LogWidget::AddEntry("Could not open project. (No \"Shaders\" folder.)");
      return false;
    }

    if (!std::filesystem::exists(projectDirectory + "/Assets/Textures"))
    {
      LogWidget::AddEntry("Could not open project. (No \"Textures\" folder.)");
      return false;
    }

    if (!std::filesystem::exists(projectDirectory + "/Assets/entry.json"))
    {
      LogWidget::AddEntry("Could not open project. (No entry file.)");
      return false;
    }

    LogWidget::AddEntry("Project opening not implemented yet.");
    return false;
  }
}