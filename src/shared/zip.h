//
//  zip.h
//  tomatenquark
//
//  Created by Lennard Berger on 26.03.20.
//

#ifndef _ZIP_H
#define _ZIP_H

extern bool addzip(const char *name, const char *mount = NULL, const char *strip = NULL);
extern bool removezip(const char *name);

#endif /* zip_h */
