assets = {}
textures = {
    texture_ball = {
        name = "texture_ball";
        path = "data/textures/ball.png"
    };
    texture_player = {
        name = "texture_player";
        path = "data/textures/animationtest.png"
    }
}
animations = {
    animation_player_down = {
        name = "animation_player_down";
        texture = "texture_player";
        frames = {
            frame1 = {32, 0, 32, 32};
            frame2 = {64, 0, 32, 32};
            frame3 = {32, 0, 32, 32};
            frame4 = {0, 0, 32, 32}
        }
    };
    animation_player_left = {
        name = "animation_player_left";
        texture = "texture_player";
        frames = {
            frame1 = {32, 32, 32, 32};
            frame2 = {64, 32, 32, 32};
            frame3 = {32, 32, 32, 32};
            frame4 = {0, 32, 32, 32}
        }
    };
    animation_player_right = {
        name = "animation_player_right";
        texture = "texture_player";
        frames = {
            frame1 = {32, 64, 32, 32};
            frame2 = {64, 64, 32, 32};
            frame3 = {32, 64, 32, 32};
            frame4 = {0, 64, 32, 32}
        }
    };
    animation_player_up = {
        name = "animation_player_up";
        texture = "texture_player";
        frames = {
            frame1 = {32, 96, 32, 32};
            frame2 = {64, 96, 32, 32};
            frame3 = {32, 96, 32, 32};
            frame4 = {0, 96, 32, 32}
        }
    };
    animation_ball = {
        name = "animation_ball";
        texture = "texture_ball";
        frames = {
            frame1 = {0, 0, 300, 300}
        }
    }
}
return assets