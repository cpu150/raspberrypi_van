#include "Van.h"

// Function declarations
void sig_handler(int sig);
void register_sig();

// Common variable
bool program_exiting = false;

int main(int argc, char const *argv[]) {
  int error_code = NO_ERROR;
  Van* van = new Van();

  register_sig();

  while (!program_exiting) {
    error_code = van->run_loop();
  }

  delete van;

  return error_code;
}

void register_sig() {
	struct sigaction sig_struct;
	sig_struct.sa_handler = sig_handler;
	sig_struct.sa_flags = 0;

	sigemptyset(&sig_struct.sa_mask);

	if (sigaction(SIGINT, &sig_struct, NULL) == -1) {
		cerr << "Problem with sigaction - SIGINT" << endl;
		exit(1);
	}

	if (sigaction(SIGTERM, &sig_struct, NULL) == -1) {
		cerr << "Problem with sigaction - SIGTERM" << endl;
		exit(1);
	}
}

void sig_handler (int signo) {
  if (signo == SIGTERM) {
    printf("[SIGTERM] - ");
  } else if (signo == SIGINT) {
    printf("[SIGINT] - ");
  }
  printf("GPIO Exiting\n");

	program_exiting = true;
}
