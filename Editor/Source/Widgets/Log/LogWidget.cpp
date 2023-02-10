/* ======================================================================== */
/*!
 * \file            LogWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Widget for displaying a log window. Code taken from imgui_demo.cpp.
 */
 /* ======================================================================== */

#include "LogWidget.hpp"

namespace Barrage
{
  LogWidget::LogWidget(EditorData& editorData, Engine& engine) :
    Widget(editorData, engine),
    buffer_(),
    filter_(),
    lineOffsets_(),
    scrollToBottom_()
  {
  }

  void LogWidget::UseWidget()
  {
    ImGui::Begin("Log");
    if (ImGui::Button("Clear")) Clear();
    ImGui::SameLine();
    bool copy = ImGui::Button("Copy");
    ImGui::SameLine();
    filter_.Draw("Filter", -100.0f);
    ImGui::Separator();
    ImGui::BeginChild("scrolling");
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
    if (copy) ImGui::LogToClipboard();
    
    if (filter_.IsActive())
    {
      const char* buf_begin = buffer_.begin();
      const char* line = buf_begin;
      for (int line_no = 0; line != NULL; line_no++)
      {
        const char* line_end = (line_no < lineOffsets_.Size) ? buf_begin + lineOffsets_[line_no] : NULL;
        if (filter_.PassFilter(line, line_end))
          ImGui::TextUnformatted(line, line_end);
        line = line_end && line_end[1] ? line_end + 1 : NULL;
      }
    }
    else
    {
      ImGui::TextUnformatted(buffer_.begin());
    }
    
    if (scrollToBottom_)
      ImGui::SetScrollHereY(1.0f);
    scrollToBottom_ = false;
    ImGui::PopStyleVar();
    ImGui::EndChild();
    ImGui::End();
  }
  
  void LogWidget::Clear()
  {
    buffer_.clear();
    lineOffsets_.clear();
  }
  
  void LogWidget::AddLog(const char* fmt, ...)
  {
    std::string addNewline = fmt;
    addNewline += "\n";

    fmt = addNewline.c_str();
    
    int old_size = buffer_.size();
    va_list args;
    va_start(args, fmt);
    buffer_.appendfv(fmt, args);
    va_end(args);
    for (int new_size = buffer_.size(); old_size < new_size; old_size++)
      if (buffer_[old_size] == '\n')
        lineOffsets_.push_back(old_size);
    scrollToBottom_ = true;
  }
}