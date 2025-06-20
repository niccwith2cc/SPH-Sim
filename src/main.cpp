#include <Particle.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <string>

int main() {

  if (!glfwInit()) return -1;
  GLFWwindow* window = glfwCreateWindow(800, 600, "Simulation", NULL, NULL);
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

  vec3 position = {.0f, .0f, .0f};
  vec3 velocity = {.0f, .0f, .0f};

  Particle p(position, velocity);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Particle Info:");
    ImGui::Text("Position: (%.2f, %.2f, %.2f)", p.getPosition().x, p.getPosition().y, p.getPosition().z);
    ImGui::Text("Velocity: (%.2f, %.2f, %.2f)", p.getVelocity().x, p.getVelocity().y, p.getVelocity().z);
    ImGui::Text("Mass: %.2f", p.getMass());
    ImGui::Text("Pressure: %.2f", p.getPressure());
    ImGui::End();

    // Main simulation window
    ImGui::SetNextWindowSize(ImVec2(600, 600), ImGuiCond_FirstUseEver);
    ImGui::Begin("Simulation");

    // Get draw list and window geometry
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 win_pos = ImGui::GetWindowPos();
    ImVec2 win_size = ImGui::GetWindowSize();
    
    // --- Simulation drawing area ---
    // Define grid parameters
    float grid_spacing = 40.0f; // pixels between grid lines
    int grid_lines = 10;        // number of lines in each direction from center

    // Center of the simulation area in window coordinates
    ImVec2 sim_center = ImVec2(win_pos.x + win_size.x * 0.5f, win_pos.y + win_size.y * 0.6f);

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
                       IM_COL32(255, 0, 0, 255), 2.0f);
    draw_list->AddLine(ImVec2(sim_center.x - grid_lines * grid_spacing, sim_center.y),
                       ImVec2(sim_center.x + grid_lines * grid_spacing, sim_center.y),
                       IM_COL32(0, 255, 0, 255), 2.0f);

    // --- Draw the particle ---
    // Map particle's (x, y) to screen coordinates
    float px = sim_center.x + p.getPosition().x * grid_spacing;
    float py = sim_center.y - p.getPosition().y * grid_spacing; // y axis up

    float radius = 20.0f * p.getMass();
    draw_list->AddCircleFilled(ImVec2(px, py), radius, IM_COL32(100, 200, 255, 255));

    ImGui::End();

    // Render
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}