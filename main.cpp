#include <Novice.h>
#include <Math.h>
#define _USE_MATH_DEFINES
#include <algorithm>
#include <String.h>

const char kWindowTitle[] = "GC1A_11_ヨ_カンリン_タイトル";


struct Vector2
{
	float x;
	float y;
};

struct Vector2I
{
	int x;
	int y;
};
Vector2I mouse;
Vector2I premouse;
Vector2I startpoint = {640,320};

struct Drag
{
	Vector2 position;
	int texture;
	unsigned int color;
};

struct Player
{
	Vector2 position;
	Vector2 velocity;
	float speed;
	float direction;
	int size=10;
	int range;
	Drag drag[10];
	int texture;
	unsigned int color;
};
Player interceptor[5];
int interceptorInCharge = 0;
int interceptorTimer = 240;
const int interceptorTime = 240;

struct Target
{
	Vector2 position;
	int size;
	int hp;
	int texture;
	unsigned int color;
};
Target target;

struct Stage
{
	int maxInterceptorCount = 3;
};
Stage stage[7];
int currentStage = 0;

int chargeRange = 250;
int mouseIspressed = 0;
int gamePhase = 3;
int inPhaseControll = 2;
int IPC3_2Status = 0; //0:待機 1:発射準備 2:発射中 3:着弾

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	
	interceptor[interceptorInCharge].position.x = (float)startpoint.x;
	interceptor[interceptorInCharge].position.y = (float)startpoint.y;
	interceptor[0].color = GREEN;
	interceptor[1].color = BLUE;
	interceptor[2].color = RED;
	interceptor[3].color = BLACK;
	interceptor[4].color = WHITE;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		premouse = mouse;
		Novice::GetMousePosition(&mouse.x, &mouse.y);

		if(gamePhase == 0) //title
		{
			if(inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 1) //tutorial
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 2) //stage menu
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 3) //game

		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2) //main
			{
				float length = (float)sqrt((mouse.y - startpoint.y) * (mouse.y - startpoint.y) + (mouse.x - startpoint.x) * (mouse.x - startpoint.x));
				/*if (!Novice::IsPressMouse(0))
				{
					mouseIspressed = 0;
				}*/
				if (IPC3_2Status == 0)
				{
					if (Novice::IsPressMouse(0) && length > chargeRange)
					{
						if (mouseIspressed == 1)
						{
							mouseIspressed = 1;
						}
						else if (mouseIspressed == 0)
						{
							mouseIspressed = 2;
						}
					}
					else if (Novice::IsPressMouse(0) && length<= chargeRange)
					{
						mouseIspressed = 0;
					}
					else if (mouseIspressed == 1)
					{
						mouseIspressed = 0;
						if(length > 50)
						{
							IPC3_2Status = 1;
							interceptor[interceptorInCharge].velocity.x = interceptor[interceptorInCharge].speed * -cosf(interceptor[interceptorInCharge].direction);
							interceptor[interceptorInCharge].velocity.y = interceptor[interceptorInCharge].speed * -sinf(interceptor[interceptorInCharge].direction);
						}
					}
					interceptor[interceptorInCharge].direction = atan2f((float)(mouse.y - startpoint.y), (float)(mouse.x - startpoint.x));
					if (mouseIspressed == 0)
					{
						if ( length < chargeRange)
						{

							if (Novice::IsPressMouse(0))
							{
								mouseIspressed = 1;
								interceptor[interceptorInCharge].speed = 10;
							}
							/*else if (mouseIspressed == 1)
							{
								interceptor[interceptorInCharge].speed = length - 50;
								IPC3_2Status = 1;
								mouseIspressed = 0;
							}*/

						}
					}
					
				}
				else if(IPC3_2Status==1)
				{
					for(int i=0;i< stage[currentStage].maxInterceptorCount;i++)
					{
						interceptor[i].position.x += interceptor[interceptorInCharge].velocity.x;
						interceptor[i].position.y += interceptor[interceptorInCharge].velocity.y;
					}
					interceptorTimer -= 1;
					if (interceptorTimer <= 0)
					{
						IPC3_2Status = 2;
						interceptorTimer = interceptorTime;
					}
				}
				else if (IPC3_2Status == 2)
				{
					interceptorInCharge += 1;
					interceptor[interceptorInCharge].position.x = (float)startpoint.x;
					interceptor[interceptorInCharge].position.y = (float)startpoint.y;
					IPC3_2Status = 0;
				}
				else if (IPC3_2Status == 3)
				{
				}
			
				/*if(interceptor[interceptorInCharge].position.x < 0 || interceptor[interceptorInCharge].position.x > 1280 ||
				   interceptor[interceptorInCharge].position.y < 0 || interceptor[interceptorInCharge].position.y > 720)
				{
					interceptorInCharge += 1;
					IPC3_2Status = 0;
				}*/
				Novice::ScreenPrintf(0, 20, "theta:%f length:%f", interceptor[interceptorInCharge].direction, length);
			}
			else if (inPhaseControll == 3) //sub
			{
			}
			else if (inPhaseControll == 4)
			{
			}
			else if (inPhaseControll == 5)
			{
			}
		}
		else if (gamePhase == 4)
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		if (gamePhase == 0)
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 1)
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 2)
		{
			
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
				
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 3)
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
				for (int i = 0; i < stage[currentStage].maxInterceptorCount; i++)
				{
					Novice::DrawEllipse((int)interceptor[i].position.x, (int)interceptor[i].position.y, interceptor[i].size, interceptor[i].size, 0.0f, interceptor[i].color, kFillModeSolid);
				}
				float theta = atan2f((float)(mouse.y - startpoint.y), (float)(mouse.x - startpoint.x));
				/*float length = (float)sqrt((mouse.y - startpoint.y) * (mouse.y - startpoint.y) + (mouse.x - startpoint.x) * (mouse.x - startpoint.x));
				if (length > 200)
				{
					length = 200;
				}*/
				float length = 200;
				Novice::ScreenPrintf(0, 0, "mouseX:%d mouseY:%d", mouse.x, mouse.y);
				
				Novice::ScreenPrintf(0, 40, "mouseIspressed:%d IPC3_2Status:%d", mouseIspressed, IPC3_2Status);
				Novice::ScreenPrintf(0, 60, "interceptorInCharge:%d X:%f Y:%f", interceptorInCharge, interceptor[interceptorInCharge].position.x, interceptor[interceptorInCharge].position.y);
				if (IPC3_2Status == 0)
				{
					if (mouseIspressed == 1)
					{
						Novice::DrawLine(startpoint.x, startpoint.y, startpoint.x - (int)(length * cosf(theta)), startpoint.y - (int)(length * sinf(theta)), 0xFFFFFFFF);
					}
					Novice::DrawEllipse(startpoint.x, startpoint.y, chargeRange, chargeRange, 0.0f, 0xFFFFFFFF, kFillModeWireFrame);
				}
				else if (IPC3_2Status == 1)
				{
					
				}
				else if (IPC3_2Status == 2)
				{
				}
				else if (IPC3_2Status == 3)
				{
				}
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		else if (gamePhase == 4)
		{
			if (inPhaseControll == 0)
			{
			}
			else if (inPhaseControll == 1)
			{
			}
			else if (inPhaseControll == 2)
			{
			}
			else if (inPhaseControll == 3)
			{
			}
			else if (inPhaseControll == 4)
			{
			}
		}
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
