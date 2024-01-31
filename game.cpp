#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input0>buttons[b].changed)

float player_p = 0.f;
float player_ai = 0.f;
float arena_half_size_x = 85, arena_half_size_y = 45;
float player_half_size_x = 2.5, player_half_size_y = 12;
float ball_p_x, ball_p_y, ball_dp_x = 150, ball_dp_y, ball_half_size = 1;

// Score System
int player_1_score, player_ai_score;

internal void simulate_game(Input* input, float dt) {
    // Background
    clear_screen(0xff5500);

    // Arena Rect
    draw_rect(0, 0, arena_half_size_x, arena_half_size_y, 0xffaa33);

    float speed = 50.f;

    // AI PLAYER
    if (ball_p_y > player_ai) {
        player_ai += (speed - 10.f) * dt;
    }
    if (ball_p_y < player_ai) {
        player_ai -= (speed - 10.f) * dt;
    }

    // Human Player
    if (is_down(BUTTON_UP))
    {
        player_p += speed * dt;
    } else if (is_down(BUTTON_DOWN)) {
        player_p -= speed * dt;
    }

    // Player collision checking with arena boundry
    if (player_p + player_half_size_y > arena_half_size_y) {
        player_p = arena_half_size_y - player_half_size_y;
    } else if (player_p - player_half_size_y < -arena_half_size_y) {
        player_p = -arena_half_size_y + player_half_size_y;
    }
    // AI collision checking with arena boundry
     if (player_ai + player_half_size_y > arena_half_size_y) {
        player_ai = arena_half_size_y - player_half_size_y;
    } else if (player_ai - player_half_size_y < -arena_half_size_y) {
        player_ai = -arena_half_size_y + player_half_size_y;
    }   

    // Ball
    draw_rect(ball_p_x, ball_p_y, ball_half_size, ball_half_size, 0xffff);
    ball_p_x += ball_dp_x * dt;
    ball_p_y += ball_dp_y * dt;
    
    // Ball collision with player
    if (ball_p_x + ball_half_size > 80 - player_half_size_x &&
            ball_p_x - ball_half_size < 80 + player_half_size_x &&
            ball_p_y + ball_half_size > player_p - player_half_size_y &&
            ball_p_y + ball_half_size < player_p + player_half_size_y) {
        ball_p_x = 80 - player_half_size_x - ball_half_size;
        ball_dp_x *= -1;
        // Movement of ball upon collision
        ball_dp_y = (ball_p_y - player_p)*2 + player_p * 1.5f;
    }
    // Ball collision with AI
    if (ball_p_x + ball_half_size > -80 - player_half_size_x &&
            ball_p_x - ball_half_size < -80 + player_half_size_x &&
            ball_p_y + ball_half_size > player_ai - player_half_size_y &&
            ball_p_y + ball_half_size < player_ai + player_half_size_y) {
        ball_p_x = -80 + player_half_size_x + ball_half_size;
        ball_dp_x *= -1;
        // Movement of ball upon collision with AI player
        ball_dp_y = (ball_p_y - player_ai)*2 + player_ai * 1.5f;
    }
    // Ball collision with walls (Top Wall)
    if (ball_p_y + ball_half_size > arena_half_size_y) {
        ball_p_y = arena_half_size_y - ball_half_size;
        ball_dp_y *= -1;
    } else if (ball_p_y - ball_half_size < -arena_half_size_y) {
        ball_p_y = -arena_half_size_y + ball_half_size;
        ball_dp_y *= -1;
    }
    // Ball collision with back walls
    if (ball_p_x + ball_half_size > arena_half_size_x) {
        ball_dp_x *= -1;
        ball_dp_y = 0;
        ball_p_y = 0;
        ball_p_x = 0;
        player_1_score++;
    } else if (ball_p_x - ball_half_size < -arena_half_size_x) {
        ball_dp_x *= -1;
        ball_dp_y = 0;
        ball_p_y = 0;
        ball_p_x = 0;
        player_ai_score++;
    }

    // Drawing the score
    draw_number(player_1_score, -10, 40, 1.f, 0xff5687);
    draw_number(player_ai_score, 10, 40, 1.f, 0xff5687);

    // Player 1
    draw_rect(80, player_p, player_half_size_x, player_half_size_y, 0xff0000);
    // Player 2
    draw_rect(-80, player_ai, player_half_size_x, player_half_size_y, 0xff0000);
}