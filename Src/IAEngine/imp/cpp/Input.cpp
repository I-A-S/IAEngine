#include <IAEngine/Input.hpp>

#include <SDL3/SDL_events.h>

namespace ia::iae
{
    struct InputDirection
    {
        iam::Vec2f Velocity{};
        Input::DirectionalInput Direction{Input::DirectionalInput::NONE};
    };

    STATIC CONSTEXPR InputDirection INPUT_TO_DIRECTION_MAP[] = {
        {iam::Vec2f{0.0f, 0.0f}, Input::DirectionalInput::NONE},       /* 0 */
        {iam::Vec2f{1.0f, 0.0f}, Input::DirectionalInput::RIGHT},      /* D */
        {iam::Vec2f{-1.0f, 0.0f}, Input::DirectionalInput::LEFT},       /* A */
        {iam::Vec2f{0.0f, 0.0f}, Input::DirectionalInput::NONE},       /* A, D */
        {iam::Vec2f{0.0f, 1.0f}, Input::DirectionalInput::DOWN},       /* S */
        {iam::Vec2f{1.0f, 1.0f}, Input::DirectionalInput::DOWN_RIGHT}, /* S, D */
        {iam::Vec2f{-1.0f, 1.0f}, Input::DirectionalInput::DOWN_LEFT},  /* S, A */
        {iam::Vec2f{0.0f, 0.0f}, Input::DirectionalInput::NONE},       /* S, A, D */
        {iam::Vec2f{0.0f, -1.0f}, Input::DirectionalInput::UP},         /* W */
        {iam::Vec2f{1.0f, -1.0f}, Input::DirectionalInput::UP_RIGHT},   /* W, D */
        {iam::Vec2f{-1.0f, -1.0f}, Input::DirectionalInput::UP_LEFT},    /* W, A */
        {iam::Vec2f{0.0f, 0.0f}, Input::DirectionalInput::NONE},       /* W, A, D */
        {iam::Vec2f{0.0f, 0.0f}, Input::DirectionalInput::NONE},       /* W, S */
        {iam::Vec2f{0.0f, 0.0f}, Input::DirectionalInput::NONE},       /* W, S, D */
        {iam::Vec2f{0.0f, 0.0f}, Input::DirectionalInput::NONE},       /* W, S, A */
        {iam::Vec2f{0.0f, 0.0f}, Input::DirectionalInput::NONE},       /* W, S, A, D */
    };

    BOOL Input::s_keys[256];
    BOOL Input::s_prevKeys[256];

    VOID Input::Initialize()
    {
        memset(s_keys, 0, sizeof(s_keys));
        memset(s_prevKeys, 0, sizeof(s_prevKeys));
    }

    VOID Input::OnEvent(IN PVOID _event)
    {
        const auto event = (SDL_Event *) _event;
        if (event->type == SDL_EVENT_KEY_DOWN)
        {
            s_keys[event->key.scancode] = true;
        }
        else if (event->type == SDL_EVENT_KEY_UP)
        {
            s_keys[event->key.scancode] = false;
        }
        memcpy(s_prevKeys, s_keys, sizeof(s_prevKeys));
    }

    iam::Vec2f Input::GetDirectionalInput()
    {
        return INPUT_TO_DIRECTION_MAP[(IsKeyDown(Input::KEY_W) << 3) | (IsKeyDown(Input::KEY_S) << 2) |
                                      (IsKeyDown(Input::KEY_A) << 1) | (IsKeyDown(Input::KEY_D) << 0)]
            .Velocity;
    }

    iam::Vec2f Input::GetDirectionalInput(OUT DirectionalInput &direction)
    {
        const auto dir = INPUT_TO_DIRECTION_MAP[(IsKeyDown(Input::KEY_W) << 3) | (IsKeyDown(Input::KEY_S) << 2) |
                                                (IsKeyDown(Input::KEY_A) << 1) | (IsKeyDown(Input::KEY_D) << 0)];
        direction = dir.Direction;
        return dir.Velocity;
    }
} // namespace ia::iae