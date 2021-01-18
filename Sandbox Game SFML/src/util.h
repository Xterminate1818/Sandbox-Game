#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

float clamp(float min, float max, float val);

int clamp(int min, int max, int val);

float magnitude(Vector2f vec);

Vector2f normalize(Vector2f vec);

Vector2f lerp(Vector2f start, Vector2f end, float percent);

float lerp(float start, float end, float percent);

Color lerp(Color start, Color end, float percent);