#include <catch2/catch_all.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../core/rendering/WindowManager.hpp"

using Barrage::WindowManager;

// Running this testing module makes every linux machine go crazy.
// Every single one--up to this point.
// So for the meantime, I am not compiling this for Linux.
TEST_CASE("Windowing System")
{
  // Create a window to test.
  WindowManager windowing;
  // Get the internal handle the window has.
  GLFWwindow* internalHandle = nullptr;
  // Get the handle to the window settings.
  const WindowManager::WindowData& settings = windowing.GetSettings();
  // Get the initial title of the window.
  std::string startTitle = "Taking over the cosmos...";
  // Create the title to change the window's title later on.
  std::string changedTitle = "Preparing for the tournament...";
  // Initialize the windowing system.
  WindowManager::WindowData initialSettings = { 1440, 720, false, startTitle };
  windowing.Initialize(initialSettings);
  // And get the internal pointer to the window.
  internalHandle = windowing.GetInternalHandle();
  // Check that the window handle actually exists.
  REQUIRE(internalHandle);

    // Test the initial settings on the window.
  SECTION("Testing initial settings.")
  {
    //! Saves the current dimensions of the window itself.
    glm::ivec2 currentDim(0, 0);
    glfwGetWindowSize(internalHandle, &currentDim.x, &currentDim.y);
    // Test the initial size of the windowing system.
    REQUIRE(currentDim == glm::ivec2(initialSettings.width_, initialSettings.height_));
    // Test to see if the border if turned off.
    bool decorated = glfwGetWindowAttrib(internalHandle, GLFW_DECORATED);
    REQUIRE(decorated == initialSettings.decorated_);
    // Test to see if the title got set correctly.
    REQUIRE(startTitle == windowing.GetSettings().title_);
  }

  SECTION("Test changing the window's size.")
  {
    // Test whether the window and the settings change
    // both in the settings and the actual window.
    //! The new set of dimensions for the window.
    glm::ivec2 newDim(1920, 1080);
    //! Saves the current dimensions of the window itself.
    glm::ivec2 currentDim(0, 0);
    // Change the dimensions.
    windowing.Resize(newDim.x, newDim.y);
    // Get the dimensions of the window.
    glfwGetWindowSize(internalHandle, &currentDim.x, &currentDim.y);
    // Test both the actual window dimensions and what the settings
    // say.
    REQUIRE(newDim.x == currentDim.x);
    REQUIRE(newDim.y == currentDim.y);
    REQUIRE(newDim.x == settings.width_);
    REQUIRE(newDim.y == settings.height_);
  }

  SECTION("Test changing the window's decoration.")
  {
    // Flip whether the decoration is on or not.
    bool newDecoration = !settings.decorated_;
    // Flip the window's decoration.
    windowing.ChangeDecoration(newDecoration);
    // Now check the decorations.
    bool currentDecoration = glfwGetWindowAttrib(internalHandle, GLFW_DECORATED);
    REQUIRE(currentDecoration == newDecoration);
    REQUIRE(settings.decorated_ == newDecoration);
  }

  SECTION("Test changing the window's title.")
  {
    // Change the dimensions of the window.
    windowing.ChangeTitle(changedTitle);
    // And check if the settings changed accordingly.
    REQUIRE(changedTitle == settings.title_);
  }

  SECTION("Check that all the settings can be changed with one function.")
  {
    WindowManager::WindowData newData = { 800, 600, true, startTitle };
    windowing.Change(newData);
    // Check whether all the settings actually changed in the data.
    REQUIRE(settings.decorated_ == newData.decorated_);
    REQUIRE(settings.height_ == newData.height_);
    REQUIRE(settings.width_ == newData.width_);
    REQUIRE(settings.title_ == newData.title_);

    // Check whether the window actually changed.

    //! Check the dimensions of the window.
    glm::ivec2 currentDim(0, 0);
    glfwGetWindowSize(internalHandle, &currentDim.x, &currentDim.y);
    //! Check the decoration of the window.
    bool decorated = glfwGetWindowAttrib(internalHandle, GLFW_DECORATED);

    // Check for the current window attributes.
    REQUIRE(settings.decorated_ == decorated);
    REQUIRE(settings.width_ == currentDim.x);
    REQUIRE(settings.height_ == currentDim.y);
  }

  SECTION("Check the focus feature for the system.")
  {
    // Onfocus the window and check whether the window is
    // actually focused.
    glfwIconifyWindow(internalHandle);
    //glfwSetWindowAttrib(internalHandle, GLFW_FOCUSED, GLFW_FALSE);
    REQUIRE(windowing.IsFocused() == false);
    // Focus the window and check if the system acknowledges that.
    windowing.Focus();
    REQUIRE(windowing.IsFocused() == true);
  }

  SECTION("Check that making a window does not leak memory.")
  {
    // Remake the window.
    windowing.RecreateOsWindow(settings);
  }

  SECTION("Test copy constructor and assignment operator.")
  {
    //! Make a copy of the system.
    WindowManager firstCopy(windowing);
    //! The dummy settings to clear the data
    WindowManager::WindowData clearSettings = { 1, 1, false, startTitle };
    // Check that settings are equivalent.
    const WindowManager::WindowData& copyData = firstCopy.GetSettings();
    REQUIRE(copyData.width_ == settings.width_);
    REQUIRE(copyData.height_ == settings.height_);
    REQUIRE(copyData.decorated_ == settings.decorated_);
    REQUIRE(copyData.title_ == settings.title_);
    // Clear the settings and test the assignment operator.
    firstCopy.Change(clearSettings);
    firstCopy = windowing;
    REQUIRE(copyData.width_ == settings.width_);
    REQUIRE(copyData.height_ == settings.height_);
    REQUIRE(copyData.decorated_ == settings.decorated_);
    REQUIRE(copyData.title_ == settings.title_);
  }
  // Finally, shutdown the window to avoid any memory leaks.
  windowing.Shutdown();
};