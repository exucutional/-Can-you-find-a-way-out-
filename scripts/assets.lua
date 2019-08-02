assets = {}
textures = {
    texture_ball = {
        name = "texture_ball";
        path = "data/textures/ball.png"
    };
    texture_player = {
        name = "texture_player";
        path = "data/textures/player_sheet.png"
    };
    texture_bullet = {
        name = "texture_bullet";
        path = "data/textures/bullet.png"
    };
    texture_wall = {
        name = "texture_wall";
        path = "data/textures/wall64.png"
    };
    texture_tiles = {
        name = "texture_tiles";
        path = "data/textures/tile_set.png"
    }
}
animations = {
    animation_ball = {
        name = "animation_ball";
        texture = "texture_ball";
        frames = {
            {0, 0, 300, 300}
        }
    };
    animation_bullet = {
        name = "animation_bullet";
        texture = "texture_bullet";
        frames = {
            {0, 0, 16, 8}
        }
    };
    animation_wall = {
        name = "animation_wall";
        texture = "texture_wall";
        frames = {
            {0, 0, 64, 64}
        }
    };
    animation_player_attack = {
        name = "animation_player_attack";
        texture = "texture_player";
        frames = {
            {0, 0, 160, 160};
            {160, 0, 160, 160};
            {320, 0, 160, 160};
            {480, 0, 160, 160}
        }
    };
    animation_player_idle = {
        name = "animation_player_idle";
        texture = "texture_player";
        frames = {
            {0, 160, 160, 160};
            {160, 160, 160, 160};
            {320, 160, 160, 160};
            {480, 160, 160, 160}
        }
    };
    animation_player_walk = {
        name = "animation_player_walk";
        texture = "texture_player";
        frames = {
            {0, 320, 160, 160};
            {160, 320, 160, 160};
            {320, 320, 160, 160};
            {480, 320, 160, 160}
        }
    };
    animation_wall_right_down_corner = {
        name = "animation_wall_right_down_corner";
        texture = "texture_tiles";
        frames = {
            {48, 144, 16, 16};
        }
    };
    animation_wall_left_down_corner = {
        name = "animation_wall_left_down_corner";
        texture = "texture_tiles";
        frames = {
            {32, 144, 16, 16};
        }
    };
    animation_wall_right_up_corner = {
        name = "animation_wall_right_up_corner";
        texture = "texture_tiles";
        frames = {
            {48, 128, 16, 16};
        }
    };
    animation_wall_right_up_corner_top = {
        name = "animation_wall_right_up_corner_top";
        texture = "texture_tiles";
        frames = {
            {48, 112, 16, 16};
        }
    };
    animation_wall_left_up_corner = {
        name = "animation_wall_left_up_corner";
        texture = "texture_tiles";
        frames = {
            {32, 128, 16, 16}
        }
    };
    animation_wall_left_up_corner_top = {
        name = "animation_wall_left_up_corner_top";
        texture = "texture_tiles";
        frames = {
            {32, 112, 16, 16};
        }
    };
    animation_wall_vertical_left = {
        name = "animation_wall_vertical_left";
        texture = "texture_tiles";
        frames = {
            {16, 128, 16, 16};
        }
    };
    animation_wall_vertical_right = {
        name = "animation_wall_vertical_right";
        texture = "texture_tiles";
        frames = {
            {0, 128, 16, 16};
        }
    };
    animation_wall_horizontal_top = {
        name = "animation_wall_horizontal_top";
        texture = "texture_tiles";
        frames = {
            {32, 0, 16, 16};
        }
    };
    animation_wall_horizontal_rightend_top = {
        name = "animation_wall_horizontal_rightend_top";
        texture = "texture_tiles";
        frames = {
            {48, 0, 16, 16};
        }
    };
    animation_wall_horizontal_leftend_top = {
        name = "animation_wall_horizontal_leftend_top";
        texture = "texture_tiles";
        frames = {
            {16, 0, 16, 16};
        }
    }
}
return assets