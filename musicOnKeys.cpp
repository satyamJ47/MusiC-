#include <iostream>
#include <windows.h>

using namespace std;

// #pragma comment(lib, "winmm.lib")

int main()
{
    cout << "Welcome to the Music Player!" << endl;

    // Initialize variables to control audio playback
    bool isPlaying = false;
    bool spacebarPressed = false;   // Track the spacebar state
    bool rightArrowPressed = false; // Track the rightArrow state
    bool leftArrowPressed = false;  // Track the leftArrow state
    LPCWSTR soundFiles[] = {L"sample.wav", L"pillInIbiza.wav"};

    int len = sizeof(soundFiles) / sizeof(soundFiles[0]);
    // Iterator initilize to first song
    int cur = 0;
    cout << "Instructions: Spacebar (Pause/Play), Next (Right Arrow), Previous (Left Arrow), Exit (Q)" << endl;
    while (true)
    {

        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            if (!spacebarPressed)
            {
                spacebarPressed = true; // Mark the spacebar as pressed
                if (isPlaying)
                {
                    PlaySoundW(NULL, 0, 0); // Pause the sound
                    isPlaying = false;
                    cout << "Paused" << endl;
                }
                else
                {
                    PlaySoundW(soundFiles[cur], NULL, SND_FILENAME | SND_ASYNC); // Play the sound
                    isPlaying = true;
                    cout << "Playing" << endl;
                }
            }
        }
        else
        {
            spacebarPressed = false; // Reset the spacebar state when it's released
        }

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            // Handle next track logic here
            if (!rightArrowPressed)
            {
                rightArrowPressed = true;
                cout << "Next track" << endl;
                cur = (cur + 1) % len;
                PlaySoundW(soundFiles[cur], NULL, SND_FILENAME | SND_ASYNC);
            }
        }
        else
        {
            rightArrowPressed = false;
        }

        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            if (!leftArrowPressed)
            {
                leftArrowPressed = true;
                cur = (cur - 1 + len) % len;
                PlaySoundW(soundFiles[cur], NULL, SND_FILENAME | SND_ASYNC);
            }
            // Handle previous track logic here
            cout << "Previous track" << endl;
        }
        else
        {
            leftArrowPressed = false;
        }

        if (GetAsyncKeyState(VK_TAB) & 0x8000)
        {
            if (isPlaying)
            {
                PlaySoundW(NULL, 0, 0); // Stop the sound if playing
            }
            cout << "Application exited." << endl;
            return 0;
        }
    }
}
