#include "Particle.h"
#include "Vec3.h"
#include "Globals.h"
#include "imgui.h"
#include <vector>
#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


int startWin(GLFWwindow* window){
  if (!window){
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void) io;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 130");

  return 0;
}

void drawParticleInfo(const std::vector<Particle>& particleList){
  ImGui::Begin("Particle Info: ");
  
  for (auto & p : particleList){
    ImGui::Text("Position: (%.2f, %.2f, %.2f)", p.getPosition().getX(), p.getPosition().getY(), p.getPosition().getZ());
    ImGui::Text("Velocity: (%.2f, %.2f, %.2f)", p.getVelocity().getX(), p.getVelocity().getY(), p.getVelocity().getZ());
    ImGui::Text("Acceleration: (%.2f, %.2f, %.2f)", p.getAcc().getX(), p.getAcc().getY(), p.getAcc().getZ());
    ImGui::Text("Mass: %.2f", p.getMass());
    ImGui::Text("Pressure: %.2f", p.getPressure());
    ImGui::Text(" ");
  }
  ImGui::End();
}

void drawGridParticles(std::vector<Particle> &particleList){

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  if (!particleList.empty())
    drawParticleInfo(particleList);

  // Main simulation window
  ImGui::SetNextWindowSize(ImVec2(2560, 1600), ImGuiCond_FirstUseEver);
  ImGui::Begin("Simulation Window");

  // Get draw list and window geometry
  ImDrawList* draw_list = ImGui::GetWindowDrawList();
  ImVec2 win_pos = ImGui::GetWindowPos();
  ImVec2 win_size = ImGui::GetWindowSize();
  
  // --- Simulation drawing area ---
  // Define grid parameters
  constexpr float grid_spacing = 20.0f; // pixels between grid lines
  constexpr int grid_lines = 50;        // number of lines in each direction from center

  // Center of the simulation area in window coordinates
  ImVec2 sim_center = ImVec2(win_pos.x + win_size.x * 0.5f, win_pos.y + win_size.y * 0.5f);

  // Draw grid lines
  for (int i = -grid_lines; i <= grid_lines; ++i) {
      // Vertical lines
      float x = sim_center.x + i * grid_spacing;
      draw_list->AddLine(ImVec2(x, sim_center.y - grid_lines * grid_spacing),
                          ImVec2(x, sim_center.y + grid_lines * grid_spacing),
                          IM_COL32(150, 150, 150, 80));
      // Horizontal lines
      float y = sim_center.y + i * grid_spacing;
      draw_list->AddLine(ImVec2(sim_center.x - grid_lines * grid_spacing, y),
                          ImVec2(sim_center.x + grid_lines * grid_spacing, y),
                          IM_COL32(150, 150, 150, 80));
      // Numbering
      if (i != 0) {
          draw_list->AddText(ImVec2(x + 2, sim_center.y + 2), IM_COL32(180,180,180,180), std::to_string(i).c_str());
          draw_list->AddText(ImVec2(sim_center.x + 2, y + 2), IM_COL32(180,180,180,180), std::to_string(-i).c_str());
      }
  }
  // Draw axis lines
  draw_list->AddLine(ImVec2(sim_center.x, sim_center.y - grid_lines * grid_spacing),
                      ImVec2(sim_center.x, sim_center.y + grid_lines * grid_spacing),
                      IM_COL32(150, 150, 150, 255), 2.0f);
  draw_list->AddLine(ImVec2(sim_center.x - grid_lines * grid_spacing, sim_center.y),
                      ImVec2(sim_center.x + grid_lines * grid_spacing, sim_center.y),
                      IM_COL32(150, 150, 150, 255), 2.0f);

  draw_list->AddRect(ImVec2(sim_center.x + boundary.xmin * grid_spacing, sim_center.y - boundary.ymax * grid_spacing),
                     ImVec2(sim_center.x + boundary.xmax * grid_spacing, sim_center.y - boundary.ymin * grid_spacing),                     
                     IM_COL32(200, 50, 50, 255), 2.0f);

  // --- Draw the particle ---
  // Map particle's (x, y) to screen coordinates
  for (auto & p : particleList){
    float px = sim_center.x + p.getPosition().getX() * grid_spacing;
    float py = sim_center.y - p.getPosition().getY() * grid_spacing; // y axis up
    float const baseRad = 5.0f;
    float const scale = 3.0f;
    float radius = baseRad + scale * std::log10(p.getMass());
    draw_list->AddCircleFilled(ImVec2(px, py), radius, IM_COL32(100, 200, 255, 255));   
  }

  ImGui::End();
}

void Render(GLFWwindow* window){
  ImGui::Render();
  int display_w, display_h;
  glfwGetFramebufferSize(window, &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  glfwSwapBuffers(window);
}