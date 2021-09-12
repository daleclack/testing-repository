//This File is some extensions of image
//Note that this is the first edition,may needs improvement
static const char * const supported_globs[]={
    "*.bmp",
    "*.apng",
    "*.avif",
    "*.cod",
    "*.gif",
    "*.ief",
    "*.jpe",
    "*.jpeg",
    "*.jpg",
    "*.jfif",
    "*.pjpeg",
    "*.pjp",
    "*.svg",
    "*.png",
    "*.tif",
    "*.tiff",
    "*.ras",
    "*.cmx",
    "*.ico",
    "*.pnm",
    "*.pbm",
    "*.pgm",
    "*.ppm",
    "*.rgb",
    "*.webp",
    "*.xbm",
    "*.xpm",
    "*.xwd",
    NULL
};

static inline bool mime_type_supported(){
    #ifdef G_OS_WIN32
        return false;
    #else
        return true;
    #endif
}
