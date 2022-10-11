
#ifndef EDITOR_CAMERAPATHS_H
#define EDITOR_CAMERAPATHS_H

/*** Définitions ********************************************************/

typedef struct CAMERAPATH {
	LONG	PathId;
	BOOL	ShowCell;
} CAMERAPATH;

typedef struct CAMERAPATHDESC {
	LONG	 Path;
	UINT	 Bitmap;
	char	*Description;
	BOOL	 ShowCell;
} CAMERAPATHDESC;

#endif //EDITOR_CAMERAPATHS_H
