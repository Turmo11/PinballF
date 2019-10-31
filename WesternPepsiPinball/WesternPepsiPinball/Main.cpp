#include <stdlib.h>

#include "p2Log.h"
#include "p2Defs.h"
#include "Globals.h"
#include "Application.h"

// This is needed here because SDL redefines main function
// do not add any other libraries here, instead put them in their modules
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};


Application* App = NULL;

int main(int argc, char* args[])
{
	LOG("Engine starting ... %d");

	main_states state = MAIN_CREATION;
	int main_return = EXIT_FAILURE;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{

			// Allocate the engine --------------------------------------------
		case MAIN_CREATION:
			LOG("CREATION PHASE ===============================");

			App = new Application();
			state = MAIN_START;
			break;
		
			// Call all modules before first frame  ----------------------------
		case MAIN_START:
			LOG("START PHASE ===============================");
			if (App->Init() == true)
			{
				state = MAIN_UPDATE;
				LOG("UPDATE PHASE ===============================");
			}
			else
			{
				state = MAIN_EXIT;
				LOG("ERROR: Start failed");
			}
			break;

			// Loop all modules until we are asked to leave ---------------------
		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				LOG("Application Update exits with ERROR");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
		break;

			// Cleanup allocated memory -----------------------------------------
		case MAIN_FINISH:

			LOG("-------------- Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG("Application CleanUp exits with ERROR");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;
		}
	}

	LOG("... Bye! :)\n");

	// Dump memory leaks
	return main_return;
}