global_variable float render_scale = 0.01f;

internal void render_backround() {
    u32* pixel = (u32*)render_state.memory;
    for (int y = 0; y < render_state.height; y++) {
        for (int x = 0; x < render_state.width; x++) {
            *pixel++ = 0xff5500;
        }
    }
}

internal void clear_screen(u32 pixel_clear_colour) {
    u32 * pixel = (u32*)render_state.memory;
    for (int y = 0; y < render_state.height; y++) {
        for (int x = 0; x < render_state.width; x++) {
            *pixel++ = pixel_clear_colour;
        }
    }
}

internal void draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 colour) {

    x0 = clamp(0, x0, render_state.width);
    x1 = clamp(0, x1, render_state.width);
    y0 = clamp(0, y0, render_state.height);
    y1 = clamp(0, y1, render_state.height);

    for (int y = y0; y < y1; y++) {
        u32* pixel = (u32*)render_state.memory + x0 + y*render_state.width;       
        for (int x = x0; x < x1; x++) {
            *pixel++ = colour;
        }
    }
}

internal void draw_rect(float x, float y, float half_size_x, float half_size_y, u32 colour) {
    x *= render_state.height * render_scale;
    y *= render_state.height * render_scale;
    half_size_x *= render_state.height * render_scale;
    half_size_y *= render_state.height * render_scale;

    x += render_state.width / 2.f;
    y += render_state.height /2.f;

    // Change to pixels
    int x0 = x - half_size_x;
    int x1 = x + half_size_x; 
    int y0 = y - half_size_y;
    int y1 = y + half_size_y;

    draw_rect_in_pixels(x0, y0, x1, y1, colour);
}

internal void draw_number(int number, float x, float y, float size, u32 colour) {
    float half_size = size * 0.5f;
    switch (number) {
        case 0: {
            draw_rect(x - size, y, half_size, 2.5f * size, colour);
            draw_rect(x + size, y, half_size, 2.5f * size, colour);
            draw_rect(x, y + size * 2.0f, half_size, half_size, colour);
            draw_rect(x, y - size * 2.0f, half_size, half_size, colour);
        } break;
        case 1: {
            draw_rect(x + size, y, half_size, 2.5f * size, colour);
        } break;
        case 2: {
            draw_rect(x, y + size * 2.f, 1.5f * size, half_size, colour);
            draw_rect(x, y, 1.5f * size, half_size, colour);
            draw_rect(x, y - size * 2.f, 1.5f * size, half_size, colour);
            draw_rect(x + size, y + size, half_size, half_size, colour);
            draw_rect(x - size, y - size, half_size, half_size, colour);
        } break;
        case 3: {
            draw_rect(x - half_size, y + size * 2.f, size, half_size, colour);
            draw_rect(x - half_size, y, size, half_size, colour);
            draw_rect(x - half_size, y - size * 2.f, size, half_size, colour);
            draw_rect(x + size, y, half_size, 2.f * size, colour);
        }
    }
}