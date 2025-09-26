#include <Particle.h>
#include <Vec3.h>
#include <Simulate.h>
#include <Globals.h>
#include <Draw.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <string>
#include <vector>

#define DEBUG 1

int main() {

  // initial conditions
  std::vector<Particle> particleList;
  int nb = 1;
  float finalTime = 10.0f;
  float time = 0.0f;
  float dt = 0.0f;
  int timeSteps = 0;

  bool status = DEBUG;

  spawnGrid(particleList, nb);

  if (!glfwInit()) return -1;
  GLFWwindow* window = glfwCreateWindow(1920, 1200, "Windowed View", NULL, NULL);
  int fail = startWin(window);
  if (fail == -1) return -1;

  while (!glfwWindowShouldClose(window)) {

    glfwPollEvents(); // better to keep poll events in the main loop

    // Draw
    drawGridParticles(particleList);

    // simulate
    if (time < finalTime){
      simulateStep(particleList, time, dt, timeSteps, status);
    }

    // Render
    Render(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}