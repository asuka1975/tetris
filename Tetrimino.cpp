#include "Tetrimino.h"

static Matrix4 i_mino{
	"    ",
	"CCCC",
	"    ",
	"    "
};

static Matrix4 o_mino{
	"    ",
	" YY ",
	" YY ",
	"    "
};

static Matrix4 s_mino{
	"    ",
	"  GG",
	" GG ",
	"    "
};

static Matrix4 z_mino{
	"    ",
	"RR  ",
	" RR ",
	"    ",
};

static Matrix4 j_mino{
	"    ",
	"B   ",
	"BBB ",
	"    ",
};

static Matrix4 l_mino{
	"    ",
	"   W",
	" WWW",
	"    ",
};

static Matrix4 t_mino{
	"    ",
	" MMM",
	"  M ",
	"    ",
};

static Matrix4 none{
	"    ",
	"    ",
	"    ",
	"    ",
};

static Matrix4 i_minorots[4];
static Matrix4 o_minorots[4];
static Matrix4 s_minorots[4];
static Matrix4 z_minorots[4];
static Matrix4 j_minorots[4];
static Matrix4 l_minorots[4];
static Matrix4 t_minorots[4];
static Matrix4 nonerots[4] = { none, none, none, none };

static Matrix4* allmino_version[8]{
	i_minorots,
	o_minorots,
	s_minorots,
	z_minorots,
	j_minorots,
	l_minorots,
	t_minorots,
	nonerots
};

Tetrimino::Tetrimino() : type(NONE), mino(allmino_version[(int)NONE][0]), rotation(0)
{
}

Tetrimino::Tetrimino(minotype t) : type(t), mino(allmino_version[(int)t][0]), rotation(0) {  }

Tetrimino::Tetrimino(const Tetrimino & obj) : type(obj.type), mino(obj.mino), rotation(obj.rotation)
{

}


Tetrimino::~Tetrimino()
{
	mino.~Matrix4();
}

void Tetrimino::Rotate(int direction) {
	rotation += direction + 4;
	rotation %= 4;
	mino = allmino_version[(int)type][rotation];
}

char Tetrimino::operator()(unsigned int x, unsigned int y)
{
	if (!(0 <= x <= 3) || !(0 <= y <= 3)) return '\0';
	return mino(x, y);
}

Tetrimino & Tetrimino::operator=(const Tetrimino & obj)
{
	type = obj.type;
	mino = obj.mino;
	rotation = obj.rotation;
	return *this;
}

minotype Tetrimino::GetMinotype()
{
	return type;
}

void Tetrimino::InitMino()
{
	i_minorots[0] = i_mino; i_minorots[1] = i_mino.Rot90(); i_minorots[2] = i_mino; i_minorots[3] = i_mino.Rot90();
	o_minorots[0] = o_mino; o_minorots[1] = o_mino        ; o_minorots[2] = o_mino; o_minorots[3] = o_mino        ;
	s_minorots[0] = s_mino; s_minorots[1] = s_mino.Rot90(); s_minorots[2] = s_mino; s_minorots[3] = s_mino.Rot90();
	z_minorots[0] = z_mino; z_minorots[1] = z_mino.Rot90(); z_minorots[2] = z_mino; z_minorots[3] = z_mino.Rot90();
	j_minorots[0] = j_mino; j_minorots[1] = j_mino.Rot90(); j_minorots[2] = j_mino.Rot90().Rot90(); j_minorots[3] = j_mino.Rot90().Rot90().Rot90();
	l_minorots[0] = l_mino; l_minorots[1] = l_mino.Rot90(); l_minorots[2] = l_mino.Rot90().Rot90(); l_minorots[3] = l_mino.Rot90().Rot90().Rot90();
	t_minorots[0] = t_mino; t_minorots[1] = t_mino.Rot90(); t_minorots[2] = t_mino.Rot90().Rot90(); t_minorots[3] = t_mino.Rot90().Rot90().Rot90();
}
