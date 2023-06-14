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
#include <string>

namespace Barrage
{
  ImGuiTextBuffer LogWidget::buffer_ = ImGuiTextBuffer();
  ImGuiTextFilter LogWidget::filter_ = ImGuiTextFilter();
  ImVector<int> LogWidget::lineOffsets_ = ImVector<int>();
  bool LogWidget::scrollToBottom_ = bool();
  ImVec2 LogWidget::size_ = ImVec2(0.0f, 0.0f);

  void LogWidget::Use()
  {
    ImGui::Begin("Output Log", nullptr, ImGuiWindowFlags_NoMove);
    size_ = ImGui::GetWindowSize();

    if (ImGui::Button("Clear")) Clear();
    ImGui::SameLine();
    bool copy = ImGui::Button("Copy");
    ImGui::SameLine();
    filter_.Draw("Filter", -100.0f);
    ImGui::Separator();
    ImGui::BeginChild("scrolling");
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
    if (copy) ImGui::LogToClipboard();
    
    const char* buf_begin = buffer_.begin();
    const char* line = buf_begin;
    for (int line_no = 0; line != NULL; line_no++)
    {
      const char* line_end = (line_no < lineOffsets_.Size) ? buf_begin + lineOffsets_[line_no] : NULL;
      if (!filter_.IsActive() || filter_.PassFilter(line, line_end))
        ImGui::TextUnformatted(line, line_end);
      line = line_end && line_end[1] ? line_end + 1 : NULL;
    }
    
    ImGui::Spacing();

    if (scrollToBottom_)
      ImGui::SetScrollHereY(1.0f);
    scrollToBottom_ = false;
    ImGui::PopStyleVar();
    ImGui::EndChild();
    ImGui::End();
  }
  
  ImVec2 LogWidget::GetSize()
  {
    return size_;
  }

  void LogWidget::Clear()
  {
    buffer_.clear();
    lineOffsets_.clear();
  }
  
  void LogWidget::AddEntry(const char* fmt, ...)
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

  void LogWidget::AddEntry(const std::string& text)
  {
    AddEntry(text.c_str());
  }
}