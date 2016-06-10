#pragma once

Texture* texture_create(const char* filename);
Texture* texture_create_default(const char* filename);
void texture_destroy(Texture* texture);
void texture_load(Texture* texture, const char* fillename);