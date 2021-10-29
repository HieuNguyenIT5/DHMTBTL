// thư viện tải hình ảnh
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <Vector_Matrix.h>
using namespace std;


//-------------------------------------------------------------------------------
		/*************Hướng dẫn điều khiển***************
		 *												*
		 *		w,ư		: Đi tiến						*
		 *		s		: Đi lùi						*
		 *		a		: Quay đầu						*
		 *		d		: Quay đầu						*
		 *		q		: Bắn pháo						*
		 *		->		: Quay Pháo						*
		 *		<-		: Quay pháo						*
		 *		^		: Nâng góc bắn					*
		 *		v		: Hạ góc bắn					*
		 *		m		: Mở nắp trên xe Tank			*
		 *		x,y,z	: Chỉnh Camera					*
		 *		X,Y,Z	: Chỉnh Camera					*
		 ************************************************/
		 //---------------------------------------------------------------------------------
typedef struct
{
	float xyzw[4];
	float rgba[4];
	float normal[4];
	float texture[4];
} Vertex;

Vertex Vertices[] =
{
	//Hình hộp
		// v4-v7-v6 (back - user)
{ { 0.5f, -0.5f, -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f } ,{ 0, 0,-1, 0 }, { 0.0f, 0.0f } },
{ { -0.5f, -0.5f, -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 },{ 1.0f, 0.0f  } },
{ { -0.5f, 0.5f, -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f } ,{ 0, 0,-1, 0 }, { 1.0f, 1.0f } },
// v6-v5-v4
{ { -0.5f, 0.5f, -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f } , {0, 0,-1, 0 },{ 1.0f, 1.0f  } },
{ { 0.5f, 0.5f, -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f }  ,{0, 0,-1, 0 },{ 0.0f, 1.0f   } },
{ { 0.5f, -0.5f, -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f } ,{0, 0,-1, 0 },{ 0.0f, 0.0f   } },
// v2-v3-v0 (front - user)
{ { -0.5f, -0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 0.0f, 0.0f } },
{ { 0.5f, -0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 1.0f, 0.0f } },
{ { 0.5f, 0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 1.0f, 1.0f } },
// v0-v1-v2
{ { 0.5f, 0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 1.0f, 1.0f } },
{ { -0.5f, 0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 0.0f, 1.0f } },
{ { -0.5f, -0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 0.0f, 0.0f } },
//v1-v0-v5 (top)
{ { -0.5f, 0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 0.0f, 0.0 } },
{ { 0.5f, 0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 1.0f, 0.0f } },
{ { 0.5f, 0.5f, -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 1.0f, 1.0f } },
//v5-v6-v1
{ { 0.5f, 0.5f, -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 1.0f, 1.0f } },
{ { -0.5f, 0.5f, -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 0.0f, 1.0f } },
{ { -0.5f, 0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 0.0f, 0.0f } },
// v7-v4-v3 (bottom)
{ { -0.5f, -0.5f,-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 0.0f, 0.0 } },
{ { 0.5f, -0.5f, -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 1.0f, 0.0f } },
{ { 0.5f, -0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 1.0f, 1.0f } },
// v3-v2-v7
{ { 0.5f, -0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 1.0f, 1.0f } },
{ { -0.5f, -0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 0.0f, 1.0f } },
{ { -0.5f, -0.5f, -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 0.0f, 0.0f } },
// v3-v4-v5 (right)
{ { 0.5f, -0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 0.0f, 0.0f } },
{ { 0.5f, -0.5f, -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 1.0f, 0.0f } },
{ { 0.5f, 0.5f, -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 1.0f, 1.0f } },
// v5-v0-v3
{ { 0.5f, 0.5f, -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 1.0f, 1.0f } },
{ { 0.5f, 0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 0.0f, 1.0f } },
{ { 0.5f, -0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 0.0f, 0.0f } },
// v7-v2-v1 (left)
{ { -0.5f, -0.5f, -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 0.0f, 0.0 } },
{ { -0.5f, -0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 1.0f, 0.0f } },
{ { -0.5f, 0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 1.0f, 1.0f } },
// v1-v6-v7
{ { -0.5f, 0.5f, 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 1.0f, 1.0f } },
{ { -0.5f, 0.5f, -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 0.0f, 1.0f } },
{ { -0.5f, -0.5f, -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 0.0f, 0.0f } },
//tam chóp tứ giác--------------------------------------------------------
// bottom
{ { -0.5f, -0.5f, 0.5f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f }, { 0, 0,-1, 0 },{ 0.0f, 0.0f } },
{ { 0.5f, -0.5f, -0.5f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f } , { 0, 0,-1, 0 },{ 1.0f, 0.0f }},
{ { -0.5f, -0.5f, -0.5f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f } , { 0, 0,-1, 0 },{ 1.0f, 1.0f }},
{ { 0.5f, -0.5f, -0.5f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f } , { 0, 0,-1, 0 },{ 1.0f, 1.0f }},
{ { -0.5f, -0.5f, 0.5f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f } , { 0, 0,-1, 0 },{ 0.0f, 1.0f }},
{ { 0.5f, -0.5f, 0.5f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f } , { 0, 0,-1, 0 },{ 0.0f, 0.0f }},
// right
{ { 0.0f, 0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{ 0.0f, 0.0f } },
{ { 0.5f, -0.5f, 0.5f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{ 1.0f, 0.0f } },
{ { 0.5f, -0.5f, -0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{ 1.0f, 1.0f }},
// left
{ { 0.0f, 0.5f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } , { 0, 0,-1, 0 },{ 0.0f, 0.0f }},
{ { -0.5f, -0.5f, -0.5f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f }, { 0, 0,-1, 0 },{ 1.0f, 0.0f } },
{ { -0.5f, -0.5f, 0.5f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } , { 0, 0,-1, 0 },{ 1.0f, 1.0f }},
// front
{ { 0.0f, 0.5f, 0.0f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } , { 0, 0,-1, 0 },  { 0.0f, 0.0f } },
{ { -0.5f, -0.5f, 0.5f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } , { 0, 0,-1, 0 },{ 1.0f, 0.0f }},
{ { 0.5f, -0.5f, 0.5f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f }, { 0, 0,-1, 0 },  { 1.0f, 1.0f } },
// back
{ { 0.0f, 0.5f, 0.0f, 1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{ 0.0f, 0.0f }},
{ { 0.5f, -0.5f, -0.5f,1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{ 1.0f, 0.0f }},
{ { -0.5f, -0.5f, -0.5f,1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{ 1.0f, 1.0f }},
//hình trụ
// botton
{ { 0.0f, -0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{ 0.0f, 0.0f } },
{ { 0.5f, -0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{ 1.0f, 0.0f } },//1
{ { 0.433f, -0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f}, { 0, 0,-1, 0 },{ 1.0f, 1.0f } },

{ { 0.0f, -0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }  , { 0, 0,-1, 0 },{ 0.0f, 0.0f }},
{ { 0.433f, -0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{ 1.0f, 0.0f } },//2
{ { 0.25f, -0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{ 1.0f, 1.0f } },

{ { 0.0f, -0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{ 0,0}},
{ { 0.25f, -0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{ 1,0 } },//3
{ { 0.0f, -0.5f, 0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,1 }},

{ { 0.0f, -0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{0,0 } },
{ { 0.0f, -0.5f, 0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,0 }},//4
{ { -0.25f, -0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,1 } },

{ { 0.0f, -0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{0,0 }},
{ { -0.25f, -0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,0 } },//5
{ { -0.433f, -0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,1 }},

{ { 0.0f, -0.5, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{0,0 }},
{ { -0.433f, -0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,0 } },//6
{ { -0.5f, -0.5f, 0.0f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,1 } },

{ { 0.0f, -0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{ 0,0 } },
{ { -0.5f, -0.5f, 0.0f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,0 } },//7
{ { -0.433f, -0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,1 } },

{ { 0.0f, -0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{0,0 } },
{ { -0.433f, -0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,0 } },//8
{ { -0.25f, -0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,1 } },

{ { 0.0f, -0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{0,0 } },
{ { -0.25f, -0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,0 } },//9
{ { 0.0f, -0.5f, -0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,1 } },

{ { 0.0f, -0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{ 0,0 } },
{ { 0.0f, -0.5f, -0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,0 } },//10
{ { 0.25f, -0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,1 } },

{ { 0.0f, -0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{0,0} },
{ { 0.25f, -0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,0 } },//11
{ { 0.433f, -0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,1 } },

{ { 0.0f, -0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{0,0 } },
{ { 0.433f, -0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,0 } },
{ { 0.5f, -0.5f, 0.0f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,1 } },
// face
{ { 0.5f, -0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }   ,{ 0, 0,-1, 0 }, { 0.0f, 0.0f } },
{ { 0.433f, -0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } ,{ 0, 0,-1, 0 },{ 1.0f, 0.0f  } },
{ { 0.433f, 0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }  ,{ 0, 0,-1, 0 }, { 1.0f, 1.0f } },

{ { 0.5f, 0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }    , {0, 0,-1, 0 },{ 1.0f, 1.0f  } },
{ { 0.433f, 0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }  ,{0, 0,-1, 0 },{ 0.0f, 1.0f   } },
{ { 0.5f, -0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }   ,{0, 0,-1, 0 },{ 0.0f, 0.0f   } },
// 2-----------------------------------------------------------------
{ { 0.433f, -0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } ,{ 0, 0,-1, 0 }, { 0.0f, 0.0f } },
{ { 0.25f, -0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } ,{ 0, 0,-1, 0 },{ 1.0f, 0.0f  } },
{ { 0.433f, 0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }  ,{ 0, 0,-1, 0 }, { 1.0f, 1.0f } },

{ { 0.433f, 0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }  , {0, 0,-1, 0 },{ 1.0f, 1.0f  } },
{ { 0.25f, 0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }  ,{0, 0,-1, 0 },{ 0.0f, 1.0f   } },
{ { 0.25f, -0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f}  ,{0, 0,-1, 0 },{ 0.0f, 0.0f   } },
// 3------------------------------------------------------------------
{ { 0.25f, -0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } ,{ 0, 0,-1, 0 }, { 0.0f, 0.0f } },
{ { 0.0f, -0.5f, 0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }    ,{ 0, 0,-1, 0 },{ 1.0f, 0.0f  } },
{ { 0.25f, 0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }  ,{ 0, 0,-1, 0 }, { 1.0f, 1.0f } },

{ { 0.25f, 0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }  , {0, 0,-1, 0 },{ 1.0f, 1.0f  } },
{ { 0.0f, 0.5f, 0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }     ,{0, 0,-1, 0 },{ 0.0f, 1.0f   } },
{ { 0.0f, -0.5f, 0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }    ,{0, 0,-1, 0 },{ 0.0f, 0.0f   } },
// 4------------------------------------------------------------------
{ { 0.0f, -0.5f, 0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }    ,{ 0, 0,-1, 0 }, { 0.0f, 0.0f } },
{ { -0.25f, -0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} ,{ 0, 0,-1, 0 },{ 1.0f, 0.0f  } },
{ { 0.0f, 0.5f, 0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }     ,{ 0, 0,-1, 0 }, { 1.0f, 1.0f } },

{ { 0.0f, 0.5f, 0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }     , {0, 0,-1, 0 },{ 1.0f, 1.0f  } },
{ { -0.25f, 0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } ,{0, 0,-1, 0 },{ 0.0f, 1.0f   } },
{ { -0.25f, -0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} ,{0, 0,-1, 0 },{ 0.0f, 0.0f   } },
// 5------------------------------------------------------------------
{ { -0.25f, -0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} ,{ 0, 0,-1, 0 }, { 0.0f, 0.0f } },
{ { -0.433f, -0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} ,{ 0, 0,-1, 0 },{ 1.0f, 0.0f  } },
{ { -0.25f, 0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f}  ,{ 0, 0,-1, 0 }, { 1.0f, 1.0f } },

{ { -0.25f, 0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f}  , {0, 0,-1, 0 },{ 1.0f, 1.0f  } },
{ { -0.433f, 0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } ,{0, 0,-1, 0 },{ 0.0f, 1.0f   } },
{ { -0.433f, -0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} ,{0, 0,-1, 0 },{ 0.0f, 0.0f   } },
// 6------------------------------------------------------------------
{ { -0.433f, -0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} ,{ 0, 0,-1, 0 }, { 0.0f, 0.0f } },
{ { -0.5f, -0.5f, 0.0f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }   ,{ 0, 0,-1, 0 },{ 1.0f, 0.0f  } },
{ { -0.433f, 0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } ,{ 0, 0,-1, 0 }, { 1.0f, 1.0f } },

{ { -0.433f, 0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , {0, 0,-1, 0 },{ 1.0f, 1.0f  } },
{ { -0.5f, 0.5f, 0.0f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }    ,{0, 0,-1, 0 },{ 0.0f, 1.0f   } },
{ { -0.5f, -0.5f, 0.0f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }   ,{0, 0,-1, 0 },{ 0.0f, 0.0f   } },
// 7------------------------------------------------------------------
{ { -0.5f, -0.5f, 0.0f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }   ,{ 0, 0,-1, 0 }, { 0.0f, 0.0f } },
{ { -0.433f, -0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0} ,{ 0, 0,-1, 0 },{ 1.0f, 0.0f  } },
{ { -0.5f, 0.5f, 0.0f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }    ,{ 0, 0,-1, 0 }, { 1.0f, 1.0f } },

{ { -0.5f, 0.5f, 0.0f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }    , {0, 0,-1, 0 },{ 1.0f, 1.0f  } },
{ { -0.433f, 0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} ,{0, 0,-1, 0 },{ 0.0f, 1.0f   } },
{ { -0.433f, -0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f},{0, 0,-1, 0 },{ 0.0f, 0.0f   } },
// 8------------------------------------------------------------------
{ { -0.433f, -0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f},{ 0, 0,-1, 0 }, { 0.0f, 0.0f } },
{ { -0.25f, -0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f},{ 0, 0,-1, 0 },{ 1.0f, 0.0f  } },
{ { -0.433f, 0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} ,{ 0, 0,-1, 0 }, { 1.0f, 1.0f } },

{ { -0.433f, 0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} , {0, 0,-1, 0 },{ 1.0f, 1.0f  } },
{ { -0.25f, 0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} ,{0, 0,-1, 0 },{ 0.0f, 1.0f   } },
{ { -0.25f, -0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f},{0, 0,-1, 0 },{ 0.0f, 0.0f   } },
// 9-------------------------------------------------------------------
{ { -0.25f, -0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f},{ 0, 0,-1, 0 }, { 0.0f, 0.0f } },
{ { 0.0f, -0.5f, -0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }   ,{ 0, 0,-1, 0 },{ 1.0f, 0.0f  } },
{ { -0.25f, 0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} ,{ 0, 0,-1, 0 }, { 1.0f, 1.0f } },

{ { -0.25f, 0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} , {0, 0,-1, 0 },{ 1.0f, 1.0f  } },
{ { 0.0f, 0.5f, -0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }    ,{0, 0,-1, 0 },{ 0.0f, 1.0f   } },
{ { 0.0f, -0.5f, -0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }   ,{0, 0,-1, 0 },{ 0.0f, 0.0f   } },
// 10------------------------------------------------------------------
{ { 0.0f, -0.5f, -0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }   ,{ 0, 0,-1, 0 }, { 0.0f, 0.0f } },
{ { 0.25f, -0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} ,{ 0, 0,-1, 0 },{ 1.0f, 0.0f  } },
{ { 0.0f, 0.5f, -0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }    ,{ 0, 0,-1, 0 }, { 1.0f, 1.0f } },

{ { 0.0f, 0.5f, -0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }    , {0, 0,-1, 0 },{ 1.0f, 1.0f  } },
{ { 0.25f, 0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f}  ,{0, 0,-1, 0 },{ 0.0f, 1.0f   } },
{ { 0.25f, -0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} ,{0, 0,-1, 0 },{ 0.0f, 0.0f   } },
//11-------------------------------------------------------------------
{ { 0.433f, -0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} ,{ 0, 0,-1, 0 }, { 0.0f, 0.0f } },
{ { 0.5f, -0.5f, 0.0f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }    ,{ 0, 0,-1, 0 },{ 1.0f, 0.0f  } },
{ { 0.433f, 0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } ,{ 0, 0,-1, 0 }, { 1.0f, 1.0f } },

{ { 0.433f, 0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , {0, 0,-1, 0 },{ 1.0f, 1.0f  } },
{ { 0.5f, 0.5f, 0.0f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }     ,{0, 0,-1, 0 },{ 0.0f, 1.0f   } },
{ { 0.5f, -0.5f, 0.0f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }    ,{0, 0,-1, 0 },{ 0.0f, 0.0f   } },
// 12------------------------------------------------------------------
{ { 0.433f, -0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} ,{ 0, 0,-1, 0 }, { 0.0f, 0.0f } },
{ { 0.25f, -0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} ,{ 0, 0,-1, 0 },{ 1.0f, 0.0f  } },
{ { 0.433f, 0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } ,{ 0, 0,-1, 0 }, { 1.0f, 1.0f } },

{ { 0.433f, 0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , {0, 0,-1, 0 },{ 1.0f, 1.0f  } },
{ { 0.25f, 0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } ,{0, 0,-1, 0 },{ 0.0f, 1.0f   } },
{ { 0.25f, -0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f} ,{0, 0,-1, 0 },{ 0.0f, 0.0f   } },
//top-----------------------------------------
{ { 0.0f, 0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{ 0.0f, 0.0f } },
{ { 0.5f, 0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{ 1.0f, 0.0f } },//1
{ { 0.433f, 0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f}, { 0, 0,-1, 0 },{ 1.0f, 1.0f } },

{ { 0.0f, 0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }  , { 0, 0,-1, 0 },{ 0.0f, 0.0f } },
{ { 0.433f, 0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{ 1.0f, 0.0f } },//2
{ { 0.25f, 0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{ 1.0f, 1.0f } },

{ { 0.0f,0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{ 0,0} },
{ { 0.25f, 0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{ 1,0 } },//3
{ { 0.0f, 0.5f, 0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,1 } },

{ { 0.0f, 0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{0,0 } },
{ { 0.0f, 0.5f, 0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,0 } },//4
{ { -0.25f, 0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,1 } },

{ { 0.0f, 0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{0,0 } },
{ { -0.25f, 0.5f, 0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,0 } },//5
{ { -0.433f, 0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,1 } },

{ { 0.0f, 0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{0,0 } },
{ { -0.433f, 0.5f, 0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,0 } },//6
{ { -0.5f, 0.5f, 0.0f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,1 } },

{ { 0.0f,0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{ 0,0 } },
{ { -0.5f, 0.5f, 0.0f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,0 } },//7
{ { -0.433f, 0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,1 } },

{ { 0.0f,0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{0,0 } },
{ { -0.433f, 0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,0 } },//8
{ { -0.25f, 0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,1 } },

{ { 0.0f, 0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{0,0 } },
{ { -0.25f, 0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,0 } },//9
{ { 0.0f, 0.5f, -0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,1 } },

{ { 0.0f, 0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{ 0,0 } },
{ { 0.0f, 0.5f, -0.5f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,0 } },//10
{ { 0.25f, 0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,1 } },

{ { 0.0f, 0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{0,0} },
{ { 0.25f, 0.5f, -0.433f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,0 } },//11
{ { 0.433f, 0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,1 } },

{ { 0.0f, 0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{0,0 } },
{ { 0.433f, 0.5f, -0.25f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0,-1, 0 },{1,0 } },
{ { 0.5f, 0.5f, 0.0f,1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } , { 0, 0,-1, 0 },{1,1 } }
};

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].xyzw);
const size_t NormalOffset = sizeof(Vertices[0].xyzw) + sizeof(Vertices[1].rgba);
const size_t TextureOffset = sizeof(Vertices[0].xyzw) + sizeof(Vertices[1].rgba) + sizeof(Vertices[1].normal);

int
CurrentWidth = 1280,
CurrentHeight = 720;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4 model_mat_cpp,
view_mat_cpp,
projection_mat_cpp,
model_mat_tank,
model_mat_xich,
model_mat_map;

int model_mat_location,
view_mat_location,
projection_mat_location;
// Khai báo biến hỗ trợ chuyển động
float R[] = { 0.0f,0.0f,0.0f,0,0,0.0f,0.0f,0.0f,0,0 };
float S[] = { 1.0f,1.0f,1.0f };
float T[] = { 0.0f,0.0f,0.0f,0.0f };
float ban = 0.0, giat = 0.0, monap = 0.0, cobay = 0.0, viewx = 2.0, viewy = 1.5, viewz = 2.5;

//LoadTexture đã sửa-------------------------------
bool LoadTexture(const char* file_name, GLuint* texture) {
	int x, y, n;
	int force_channels = 4;
	stbi_set_flip_vertically_on_load(true);

	unsigned char* image_data = stbi_load(file_name, &x, &y, &n, force_channels);
	if (!image_data) {
		fprintf(stderr, "ERROR: could not load %s\n", file_name);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, *texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	}
	if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
		fprintf(stderr, "WARNING: texture %s is not power-of-2 dimensions\n",
			file_name);
	}
	stbi_image_free(image_data);
	glGenTextures(1, texture);
	glActiveTexture(GL_TEXTURE0);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	GLfloat max_aniso = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_aniso);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso);
	return true;
}

// ---------------------------------------------------------------------------	
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}

// ---------------------------------------------------------------------------	
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0); // position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset); // color
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)NormalOffset); // normal
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)TextureOffset); // texture
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
}
// ---------------------------------------------------------------------------	
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
// ---------------------------------------------------------------------------	
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

// ---------------------------------------------------------------------------	
//Vẽ nền của map
void map() {
	GLuint texture;
	LoadTexture("co.png", &texture);
	mat4 instance = identity_mat4();
	instance = scale(vec3(20.0, 0.001, 20.0));
	mat4 model_wing_turet = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_wing_turet.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//Thân của xe tank
void than()
{
	mat4 instance = identity_mat4();
	instance = scale(vec3(1.5, 0.3, 1.0));
	mat4 model_wing_turet = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_wing_turet.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//Xích của xe tank
void xichTank()
{
	mat4 instance = identity_mat4();
	instance = scale(vec3(1.6, 0.25, 0.08));
	mat4 model_font = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_font.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//Bánh của xe tank
void Banh() {
	mat4 instance = identity_mat4();
	instance = scale(vec3(0.26, 0.1, 0.25));
	mat4 model_font = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_font.m);
	glDrawArrays(GL_TRIANGLES, 54, 144);
}
//Thân trên của xe tank
void tren()
{
	GLuint texture;
	LoadTexture("nen.png", &texture);
	mat4 instance = identity_mat4();
	instance = scale(vec3(0.8, 0.2, 0.5));
	mat4 model_wing_turet = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_wing_turet.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//Súng || Pháo xe tank
void duoiSung() {
	mat4 instance = identity_mat4();
	instance = scale(vec3(0.02, 0.1, 0.1));
	mat4 model_font = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_font.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void sung()
{
	mat4 instance = identity_mat4();
	instance = rotate_z(90)*scale(vec3(0.08, 1.0, 0.08));
	mat4 model_wing_turet = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_wing_turet.m);
	glDrawArrays(GL_TRIANGLES, 54, 144);
}
void dausung()
{
	mat4 instance = identity_mat4();
	instance = rotate_z(90) * scale(vec3(0.1, 0.12, 0.12));
	mat4 model_wing_turet = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_wing_turet.m);
	glDrawArrays(GL_TRIANGLES, 54, 144);
}
void Dan() {
	GLuint texture;
	LoadTexture("maudong.png", &texture);
	mat4 instance = identity_mat4();
	instance = rotate_z(90) * scale(vec3(0.05, 0.1, 0.05));
	mat4 model_wing_turet = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_wing_turet.m);
	glDrawArrays(GL_TRIANGLES, 54, 144);
}
//Nắp của xe tank
void napTank() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.01, 0.0, 0.0)) * scale(vec3(0.25, 0.1, 0.25));
	mat4 model_wing_turet = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_wing_turet.m);
	glDrawArrays(GL_TRIANGLES, 36, 18);
}
//Cây trong map
void chopCay() {
	mat4 instance = identity_mat4();
	instance = scale(vec3(0.3, 0.8, 0.3));
	mat4 model_wing_turet = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_wing_turet.m);
	glDrawArrays(GL_TRIANGLES, 36, 18);
}
void thanCay() {
	mat4 instance = identity_mat4();
	instance = scale(vec3(0.1, 1.0, 0.1));
	mat4 model_wing_turet = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_wing_turet.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void Cay(float x, float y, float z) {
	model_mat_cpp = model_mat_map * translate(vec3(x, y, z));
	thanCay();
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0, 0.8, 0.0));
	chopCay();
}
//Thùng sau xe
void boomcanh() {
	GLuint texture;
	LoadTexture("nen.png", &texture);
	mat4 instance = identity_mat4();
	instance = scale(vec3(0.2, 0.5, 0.2));
	mat4 model_wing_turet = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_wing_turet.m);
	glDrawArrays(GL_TRIANGLES, 54, 144);
}
//đèn pha
void denpha() {
	GLuint texture;
	LoadTexture("denpha.png", &texture);
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, -0.25, 0.0)) * scale(vec3(0.1, 0.03, 0.1));
	mat4 model_wing_turet = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_wing_turet.m);
	glDrawArrays(GL_TRIANGLES, 54, 144);
}
//Vẽ cờ Việt Nam gồm có cột cờ và lá cờ
void cotco() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, -0.05, 0.0)) * scale(vec3(0.01, 0.4, 0.01));
	mat4 model_wing_turet = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_wing_turet.m);
	glDrawArrays(GL_TRIANGLES, 54, 144);
}
void laco() {
	GLuint texture;
	LoadTexture("quocky.png", &texture);
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.15, 0.08, 0.0)) * scale(vec3(0.3, 0.15, 0.005));
	mat4 model_wing_turet = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_wing_turet.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void covietnam() {
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.5, 0.35, 0.45));
	cotco();
	model_mat_cpp = model_mat_cpp * rotate_y(cobay);
	laco();
}
void bia() {
	mat4 instance = identity_mat4();
	instance = scale(vec3(0.5, 0.5, 0.1));
	mat4 model_wing_turet = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_wing_turet.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void cotbia() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, -0.45, 0.0)) * scale(vec3(0.1, 0.5, 0.1));
	mat4 model_wing_turet = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_wing_turet.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void biadan(float x,float y,float z) {
	model_mat_cpp = model_mat_map * translate(vec3(x, y, z)) * rotate_y(60);
	bia();
	model_mat_cpp = model_mat_cpp * translate(vec3(0.2, 0.0, 0.0));
	cotbia();
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.40,0.0,0.0));
	cotbia();
}
// Vẽ map gồm nền + cây_________________________________________________________________________________
void Landscape() {
	map();
	model_mat_map = model_mat_cpp;
	Cay(-10.0, 0.5, -10.0);
	Cay(-10.0, 0.5, -9.0);
	Cay(-10.0, 0.5, -8.0);
	Cay(-10.0, 0.5, -7.0);
	Cay(-7.0, 0.5, -10.0);
	Cay(-7.0, 0.5, -9.0);
	Cay(-7.0, 0.5, -8.0);
	Cay(-7.0, 0.5, -7.0);
	biadan(-4,0.7,-3);
}

// Vẽ xe Tank__________________________________________________________________________________________________

void xeTang() {
	GLuint texture;
	LoadTexture("nen.png", &texture);
	//Thân xe tank
	model_mat_cpp = translate(vec3(0.0, 0.32, 0.0)) * translate(vec3(T[0], T[1], T[2])) * rotate_y(R[0]);
	than();
	//Các bộ phận gắn với thân xe tank______________________________________________________________________________________________________
	model_mat_tank = model_mat_cpp;
	//Bộ bánh + xích xe tank bên trái
	model_mat_cpp = model_mat_tank * translate(vec3(0.0, -0.18, 0.54));
	xichTank();
	model_mat_xich = model_mat_cpp;
	model_mat_cpp = model_mat_xich * rotate_x(90) * translate(vec3(0.77, 0.0, 0.0)) * rotate_y(R[3]) * rotate_y(R[4]) * rotate_y(R[5]);
	Banh();
	model_mat_cpp = model_mat_xich * rotate_x(90) * translate(vec3(-0.77, 0.0, 0.0)) * rotate_y(R[3]) * rotate_y(R[4]) * rotate_y(R[5]);
	Banh();
	//Bộ bánh + xích xe tank bên trái
	model_mat_cpp = model_mat_tank * translate(vec3(0.0, -0.18, -0.54));
	xichTank();
	model_mat_xich = model_mat_cpp;
	model_mat_cpp = model_mat_xich * rotate_x(-90) * translate(vec3(0.77, 0.0, 0.0)) * rotate_y(-R[3]) * rotate_y(R[4]) * rotate_y(R[5]);
	Banh();
	model_mat_cpp = model_mat_xich * rotate_x(-90) * translate(vec3(-0.77, 0.0, 0.0)) * rotate_y(-R[3]) * rotate_y(R[4]) * rotate_y(R[5]);
	Banh();
	//Cờ Việt Nam 
	model_mat_cpp = model_mat_tank;
	covietnam();
	//Thùng đằng sau xe tank
	model_mat_cpp = model_mat_tank * translate(vec3(-0.83, 0.2, 0.0)) * rotate_x(90);
	boomcanh();
	//Hai đèn phía trước xe
	model_mat_cpp = model_mat_tank * translate(vec3(0.515, 0.0, 0.35)) * rotate_z(90);
	denpha();
	model_mat_cpp = model_mat_tank * translate(vec3(0.515, 0.0, -0.35)) * rotate_z(90);
	denpha();
	model_mat_cpp = model_mat_tank * translate(vec3(0.0, 0.25, 0.0)) * rotate_y(R[1]);
	tren();
	//Các bộ phận gắn với thân dưới xe tank________________________________________________________________________________________________
	model_mat_tank = model_mat_cpp;
	model_mat_cpp = model_mat_tank * translate(vec3(-0.01, 0.16, 0.0)) * rotate_z(monap) ;
	//Nắp trên xe tank
	napTank();
	model_mat_cpp = model_mat_tank * translate(vec3(0.41, 0.0, 0.0));
	//Bộ phận đỡ súng duôi súng
	duoiSung();
	model_mat_cpp = model_mat_cpp * rotate_z(R[2]) * rotate_z(10) * translate(vec3(0.45, 0.0, 0.0)) * translate(vec3(giat, 0.0, 0.0));
	//Súng xe tank || Pháo xe tank
	sung();
	model_mat_cpp = model_mat_cpp * translate(vec3(0.55, 0.0, 0.0));
	//Chụp giảm thanh đầu súng
	dausung();
	model_mat_cpp = model_mat_cpp * translate(vec3(ban, 0.0, 0.));
	//Đạn trong nòng súng
	Dan();
}

// ---------------------------------------------------------------------------

void DisplayFunc(void)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.8, 0.8, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFrontFace(GL_CW);
	model_mat_cpp = identity_mat4();
	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	 //Gọi map của chương trình
	model_mat_cpp = translate(vec3(0.0, 0.0, 0.0));
	Landscape();
	//Gọi hàm xe tank;
	model_mat_cpp = model_mat_cpp * rotate_x(R[0]);
	xeTang();
	vec3 eye(viewx, viewy, viewz),
		at(0.0f, 0.0f, 0.0f),
		up(0.0f, 1.0f, 0.0f);

	view_mat_cpp = lookat(eye, at, up);
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);
	float
		znear = 0.1f,
		zfar = 5000.0f,
		fov = 50.0f,
		aspect = (float)CurrentWidth / CurrentHeight;
	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);

	glutSwapBuffers();
}

// ---------------------------------------------------------------------------	

void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

	glViewport(0, 0, CurrentWidth, CurrentHeight);
}

// ---------------------------------------------------------------------------	

void IdleFunc(void)
{
	glutPostRedisplay();
}

// ---------------------------------------------------------------------------

void KeyboardFunc(unsigned char key, int x, int y)
{

	switch (key) {
	case 27:
		exit(EXIT_SUCCESS);
		break;
	case 'w':
		R[3] -= 5.0f;
		T[0] += 0.025f * cos((R[0] * 3.14) / 180);
		T[2] -= 0.025f * sin((R[0] * 3.14) / 180);
		if (cobay == 2)
			cobay = -2;
		else
			cobay = 2;
		break;
	case 's':
		R[3] += 5.0f;
		T[0] -= 0.025f * cos((R[0] * 3.14) / 180);
		T[2] += 0.025f * sin((R[0] * 3.14) / 180);
		if (cobay == 182)
			cobay = 178;
		else
			cobay = 182;
		break;
	case 'a':

		R[0] -= 5.0f;
		R[4] -= 5.0f;
		R[5] -= 5.0f;
		break;
	case 'd':

		R[0] += 5.0f;
		R[4] += 5.0f;
		R[5] += 5.0f;
		break;
	case 'q':
		if (ban > 4)
			ban = 0;
		else{
			if (ban < 0.3)
				giat = -0.1;
			else
				giat = 0;
			ban += 0.1;
		}
		break;
	case 'Q':
		ban = 0;
		break;
	case 'm':
		if (monap == 90)
			monap = 0;
		else if (monap < 90)
			monap += 5;
		break;
	case 'x':
		viewx += 1;
		break;
	case 'y':
		viewy += 1;
		break;

	case 'z':
		viewz += 1;
		break;

	case 'X':
		viewx -= 1;
		break;

	case 'Y':
		viewy -= 1;
		break;

	case 'Z':
		viewz -= 1;
		break;
	}
}

//............................................................................

void SpecialFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
	{
		if (R[1] <= 60)
			R[1] += 5;
		return;
	}
	case GLUT_KEY_LEFT:
	{
		if (R[1] >= -60)
			R[1] -= 5;
		return;
	}
	case GLUT_KEY_UP:
	{
		if (R[2] < 35)
			R[2] += 0.5;
		return;
	}
	case GLUT_KEY_DOWN:
	{
		if (R[2] > -10)
			R[2] -= 0.5;
		return;
	}
	}
}
// ---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Xe Tang");
	glewExperimental = GL_TRUE;
	glewInit();
	CreatVaoVbo();
	CreatShaders();
	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
	glutCloseFunc(CloseFunc);
	glutMainLoop();
	return 0;
}