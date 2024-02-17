#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef unsigned int uint32;

typedef int State;

typedef enum {
	Normal,
	Accept,
	Reject,
} StateType;

typedef enum {
	Nop,
	Left,
	Right,
} CursorOp;

typedef struct {
	// State state0;
	// char char0;
	bool exist;
	State state1;
	char char1;
	CursorOp op;
} Rule;

typedef struct {
	int numStates;
	StateType* states; // [numStates]
	int numAlpha;
	char* alpha; // [numAlpha]
	// int numRules;
	// Rule* rules; // [numRules]
	Rule* rules; // [numStates*128], index = state*128 + ASCII(char)

} Machine;

int ReadNumber()
{
	int number;
	scanf("%d", &number);
	return number;
}

char ReadChar()
{
	char buffer[2];
	scanf("%s", buffer);
	return buffer[0];
}

/*
void RuleInit(Rule *self)
{
	self->state0 = ReadNumber();
	self->char0 = ReadChar();
	self->state1 = ReadNumber();
	self->char1 = ReadChar();
	switch (ReadChar()) {
	case 'L':
		self->op = Left;
		break;
	case 'R':
		self->op = Right;
		break;
	case '-':
		self->op = Nop;
		break;
	}
}
*/

void MachineInit(Machine* self)
{
	self->numStates = ReadNumber();
	self->states = (StateType*)malloc(sizeof(StateType) * self->numStates);
	for (int i = 0; i < self->numStates; i++)
		self->states[i] = Normal;
	int nAccept = ReadNumber();
	for (int i = 0; i < nAccept; i++)
		self->states[ReadNumber()] = Accept;
	int nReject = ReadNumber();
	for (int i = 0; i < nReject; i++)
		self->states[ReadNumber()] = Reject;

	self->numAlpha = ReadNumber();
	self->alpha = (char*)malloc(sizeof(char) * (self->numAlpha + 1));
	scanf("%s", self->alpha);

	int numRules = ReadNumber();
	self->rules = (Rule*)malloc(sizeof(Rule) * self->numStates * 128);
	for (int s = 0; s < self->numStates; s++)
		for (int a = 0; a < 128; a++)
			self->rules[s * 128 + a].exist = false;
	for (int i = 0; i < numRules; i++) {
		int state0 = ReadNumber();
		char char0 = ReadChar();
		Rule* pR = &self->rules[state0 * 128 + char0];
		pR->exist = true;
		pR->state1 = ReadNumber();
		pR->char1 = ReadChar();
		switch (ReadChar()) {
		case 'L':
			pR->op = Left;
			break;
		case 'R':
			pR->op = Right;
			break;
		case '-':
			pR->op = Nop;
			break;
		}
	}
}

typedef struct {
	char* cursor;
	State state;
} WorkState;

// return true if successfully moved next
bool WorkStateNext(WorkState* self, Machine* machine)
{
	/*
	int n = machine->numRules;
	Rule *rules = machine->rules;
	for (int i = 0; i < n; i++) {
		if (rules[i].state0 == self->state && rules[i].char0 == *self->cursor) {
			self->state = rules[i].state1;
			*self->cursor = rules[i].char1;
			if (rules[i].op == Right) {
				self->cursor++;
			}
			if (rules[i].op == Left) {
				self->cursor--;
			}
			return true;
		}
	}
	return false;
	*/
	Rule rule = machine->rules[self->state * 128 + *self->cursor];
	if (false == rule.exist)
		return false;
	self->state = rule.state1;
	*self->cursor = rule.char1;
	if (rule.op == Right) {
		self->cursor++;
	}
	if (rule.op == Left) {
		self->cursor--;
	}
	return true;
}

bool MachineTryInput(Machine* self, char* initCursor)
{
	WorkState state = { initCursor, 0 };
	while (WorkStateNext(&state, self) && self->states[state.state] == Normal)
		;
	return self->states[state.state] == Accept;
}

bool MachineResetString(Machine* self, uint32 stringCaseIndex, int length, char* paper)
{
	int n = self->numAlpha;
	char* alpha = self->alpha;

	// char tempPaper[32];
	// int k = 0;
	/*
	while (stringCaseIndex > 0) {
		int reminder = stringCaseIndex % n;
		// printf("%d %d %d\n", k, reminder, stringCaseIndex);
		tempPaper[k++] = alpha[reminder];
		stringCaseIndex -= reminder;
		stringCaseIndex /= n;
	}
	*/

	char* pC = &paper[length];
	while (stringCaseIndex > 0) {
		if (pC <= &paper[0])
			return false;
		int reminder = stringCaseIndex % n;
		// printf("%d %d %d\n", k, reminder, stringCaseIndex);
		*pC-- = alpha[reminder];
		stringCaseIndex -= reminder;
		stringCaseIndex /= n;
	}

	paper[0] = '#';
	// for (int i = 1; i < length - k + 1; i++)
	//   paper[i] = alpha[0];
	for (char* pC2 = paper + 1; pC2 <= pC; pC2++)
		*pC2 = alpha[0];
	/*
	for (int i = length - k + 1; i <= length; i++)
		paper[i] = tempPaper[length - i];
	*/
	paper[length + 1] = '\0';

	return true;
}

bool MachineTryLength(Machine* self, int length)
{
	char paper0[32]; // Max(length) = logNumAlpha(cases) < log2(cases) < log2(10000000) < 32
	char paper[32];
	uint32 stringCaseIndex = 0; // cases < 10000000 < Max(uint32)
	while (MachineResetString(self, stringCaseIndex, length, paper0)) {
		for (int cursorBegin = 1; cursorBegin <= length; cursorBegin++) {
			strcpy(paper, paper0);
			// printf("length=%d index=%d cursor=%d %s\n", length, stringCaseIndex, cursorBegin, paper);
			if (MachineTryInput(self, paper + cursorBegin)) {
				MachineResetString(self, stringCaseIndex, length, paper);
				printf("%d\n", cursorBegin);
				printf("%s", paper0);
				return true;
			}
			// MachineResetString(self, stringCaseIndex, length, paper);
		}
		stringCaseIndex++;
	}
	return false;
}

int main()
{
	Machine machine;
	MachineInit(&machine);

	int length = 1;
	while (false == MachineTryLength(&machine, length++))
		;
	return 0;
}
