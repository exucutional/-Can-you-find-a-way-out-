objects = {}
setting = {
    type = {
        player = 0;
        ball = 1;
        bullet = 2
    };
    type_max = 3;
    animation = {
        down = 0;
        left = 1;
        up = 2;
        right = 3
    };
    animation_max = 4;
    repulsion_rate = 50
}
dynobjlist = {
    player = {
        type = setting.type.player;
        position = {40, 40};
        animation = {
            down = "animation_player_down";
            left = "animation_player_left";
            up = "animation_player_up";
            right = "animation_player_right"
        }
    };
    ball = {
        type = setting.type.ball;
        position = {100, 100};
        animation = {
            down = "animation_ball"
        }
    };
    bullet = {
        type = setting.type.bullet;
        position = {0, 0};
        animation = {
            down = "animation_bullet"
        }
    }
}
return objects