#include <Particle.h>
#include <Vec3.h>
#include <Simulate.h>
#include <Spawn.h>
#include <Draw.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <string>
#include <vector>

int main() {

  // initial conditions
  std::vector<Particle> particleList;
  int nb = 4;
  float finalTime = 1.0f;
  float time = 0.0f;
  float dt = 0.0f;
  int timeSteps = 0;

  spawnGrid(particleList, nb);

  if (!glfwInit()) return -1;
  GLFWwindow* window = glfwCreateWindow(1920, 1200, "Windowed View", NULL, NULL);
  int fail = startWin(window);
  if (fail == -1) return -1;

  while (!glfwWindowShouldClose(window)) {
    // Draw
    draw_Grid_Particles(particleList);

    // simulate
    simulate(particleList, finalTime, time, dt, timeSteps);

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