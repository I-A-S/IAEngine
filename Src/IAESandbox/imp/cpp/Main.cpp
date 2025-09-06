#include <IAEngine/Components/SoundEmitter.hpp>
#include <IAEngine/Components/SpriteRenderer.hpp>
#include <IAEngine/IAEngine.hpp>

#include <IAEngine/Audio.hpp>

#include <iacore/file.hpp>

namespace ia
{
    SIZE_T Find(IN CONST Vector<UINT8> &vec, IN SIZE_T start)
    {
        UINT8 Sig[5] = {0x89, 0x50, 0x4E, 0x47, 0x0D};
        for (SIZE_T i = start; i < vec.size(); i++)
        {
            if (!memcmp(&vec[i], Sig, sizeof(Sig)))
                return i;
        }
        return SIZE_MAX;
    }

    iae::Engine g_engine;

    RefPtr<iae::Scene> scene;
    RefPtr<iae::Node> sprite;

    VOID InitializeGame()
    {
        auto s = iae::Audio::CreateSound(File::ReadToVector("Res/Audio/SFX/gunshot.wav"));
        s.LoopTimes() = 0;

        sprite = MakeRefPtr<iae::Node>();
        const auto spriteRenderer = sprite->AddComponent<iae::SpriteRendererComponent>();

        {
            const auto data = File::ReadToVector("Res/Graphics/iae/010_1.iae");
            IA_RELEASE_ASSERT(!memcmp(&data[0], "iae.", 4));
            const auto frameCount = *reinterpret_cast<CONST UINT32 *>(&data[6]);
            INT32 off = 10;
            for (INT32 i = 0; i < frameCount; i++)
            {
                const auto t = g_engine.CreateTexture(&data[off], data.size() - off);
                spriteRenderer->AddTexture(t);
                off = Find(data, off + 1);
                if (off == SIZE_MAX)
                    break;
            }
        }

        iae::SpriteRendererComponent::Animation anim;
        anim.ShouldLoop = false;

        anim.Keys.pushBack(
            iae::SpriteRendererComponent::AnimationKeyFrame{.Duration = 500,
                                                            .ColorOverlay = iam::Vec4f{0.25f, 0.0f, 0.0f, 1.0f},
                                                            .ShouldInterpolate = true,
                                                            .TextureHandle = 0});
        anim.Keys.pushBack(
            iae::SpriteRendererComponent::AnimationKeyFrame{.Duration = 500,
                                                            .ColorOverlay = iam::Vec4f{0.5f, 0.0f, 0.0f, 1.0f},
                                                            .ShouldInterpolate = true,
                                                            .TextureHandle = 1});
        anim.Keys.pushBack(
            iae::SpriteRendererComponent::AnimationKeyFrame{.Duration = 500,
                                                            .ColorOverlay = iam::Vec4f{0.75f, 0.0f, 0.0f, 1.0f},
                                                            .ShouldInterpolate = true,
                                                            .TextureHandle = 2});
        anim.Keys.pushBack(
            iae::SpriteRendererComponent::AnimationKeyFrame{.Duration = 500,
                                                            .ColorOverlay = iam::Vec4f{1.0f, 0.0f, 0.0f, 1.0f},
                                                            .ShouldInterpolate = true,
                                                            .TextureHandle = 3});

        spriteRenderer->AddAnimation(anim);

        spriteRenderer->BakeAnimations();

        // const auto soundEmitter = sprite->AddComponent<iae::SoundEmitterComponent>();
        // soundEmitter->SetSound(s);

        sprite->SetLocalPosition({100, 100, 0});

        scene = g_engine.CreateScene();
        scene->AddNode(sprite);

        g_engine.ChangeScene(scene);
    }

    VOID UpdateGame()
    {
    }

    VOID TerminateGame()
    {
    }
} // namespace ia

int main(int argc, char *argv[])
{
    ia::g_engine.Initialize({.GameName = "IAE Sandbox", .WindowWidth = 800, .WindowHeight = 600});

    ia::InitializeGame();

    while (!ia::g_engine.ShouldClose())
    {
        ia::g_engine.BeginFrame();

        ia::UpdateGame();

        ia::g_engine.EndFrame();
    }

    ia::TerminateGame();

    ia::g_engine.Terminate();

    return 0;
}