#pragma once
#include <optional>
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#include "../constants_storage.h"

namespace gui {

class Window {
 public:
  Window(unsigned int width, unsigned int height, const std::string &title) : window_({width, height}, title),
                                                                              time_slice_shape_({25, 25}),
                                                                              input_field_(sf::Vector2f(250, 30)) {
    InitWindow();
    InitInputFields();
    InitLabels();
    InitTimeSliceShape();
  }

  // Methods
  std::optional<int> Tick();
  void Update();
  void Clear();
  void DrawTable(const std::vector<std::vector<bool>> &table);

  // Setters
  void SetRuntime(double runtime);
  void SetTimeout(double timeout);

  // Predicates
  bool IsOpen() const noexcept;

 private:
  sf::RenderWindow window_;
  sf::Font font_;

  // Buttons
  sf::Text add_process_;
  sf::Text reset_;
  sf::RectangleShape add_process_border_;
  sf::RectangleShape reset_border_;

  // Labels
  sf::Text average_timeout_label_;
  sf::Text average_runtime_label_;

  double current_timeout_ = 0.0;
  double current_runtime_ = 0.0;

  // InputField
  sf::Text input_text_;
  sf::RectangleShape input_field_;

  // Time slice icon
  sf::RectangleShape time_slice_shape_;

  // Methods
  std::optional<int> HandleMouseButtonPressed(sf::Vector2i cursor_position);
  void ResizeWindow(sf::Event event);
  // Init
  void InitWindow();
  void InitInputFields();
  void InitLabels();
  void InitTimeSliceShape();

  // Predicates
  bool IsMouseClicked(sf::Event event);
  bool IsBackspacePressed(sf::Event event);
  bool IsDigitInput(sf::Event event);
};

} // namespace gui