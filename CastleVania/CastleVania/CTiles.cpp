#include "CTiles.h"
#define SCREEN_WIDTH 320

CTile::CTile( int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex) 
{
	this->top = top;
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

void CTile::Draw(int x, int y)
{
	CGame::GetInstance()->Draw(x, y, texture, left, top, right, bottom);
}


CTiles::CTiles(int texId, LPCWSTR filePath, D3DCOLOR color)
{
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	CTextures::GetInstance()->Add(texId, color, filePath);

	tex = CTextures::GetInstance()->Get(texId);
}

void CTiles::ReadMapTXT(LPCWSTR filePath)
{
	ifstream inp(filePath, ios::in);
	inp >> RowMap >> ColumnMap >> RowTileSet >> ColumnTileSet >> frameWidth >> frameHeight >> DrawPositionX >> DrawPositionY;
	for (int i = 0; i < RowMap; i++)
		for (int j = 0; j < ColumnMap; j++)
		{
			inp >> TileMap[i][j];
		}
	inp.close();
}

void CTiles::LoadTile() 
{

	for (int i = 0; i < RowTileSet; i++)
	{
		for (int j = 0; j < ColumnTileSet; j++)
		{
			int left = j * frameWidth; //32
			int top = i * frameHeight; //32 
			int right = left + frameWidth; //32
			int bottom = top + frameHeight; //32
			LPTILE tile = new CTile(left, top, right, bottom, tex);
			tiles.push_back(tile);
		}
	}
}

void CTiles::Render() 
{
	float cx = CGame::GetInstance()->GetCamPosX();
	int beginColumn = cx / frameWidth;
	int endColumn = cx + SCREEN_WIDTH / frameWidth + 1;
	for (int i = 0; i < RowMap; i++) {
		for (int j = beginColumn; j < endColumn; j++) {
			tiles[TileMap[i][j]]->Draw(j * frameWidth + DrawPositionX, i * frameHeight + DrawPositionY);
		}
	}
};