/*! \file parse.c
 *
 * \brief Implementation of functions to read in xml format scene files
 *
 * \author Joe Doliner
 */

#include <assert.h>
#include <stdio.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "../scene.h"
#include "../objects/geometry.h"
#include "../objects/light.h"
#include "../objects/camera.h"
#include "../objects/primitives/sphere.h"
#include "../objects/primitives/box.h"
#include "../objects/primitives/torus.h"
#include "parse.h"
#include "vector.h"
#include "string.h"

#define BAD_TAG(node) 		printf("Ignoring inimplemented tag named: %s\n", node->name)
#define GRAB_FLOAT(node) 	atof((char *)node->children->content)
#define GRAB_INT(node)		atoi((char *)node->children->content)

/* !Parse_Position
 * \brief read an xml node which is a position. it must have x,y and z tags in it
 */
void Parse_Position(xmlNodePtr pos, Vec3f_t dst) {
    xmlNodePtr cur;
    for (cur = pos->children; cur; cur = cur->next) {
	if (!xmlStrcmp(cur->name, (const xmlChar *) "x"))
	    dst[0] = GRAB_FLOAT(cur);
	else if (!xmlStrcmp(cur->name, (const xmlChar *) "y"))
	    dst[1] = GRAB_FLOAT(cur);
	else if (!xmlStrcmp(cur->name, (const xmlChar *) "z"))
	    dst[2] = GRAB_FLOAT(cur);
	else
	    BAD_TAG(cur);
    }
}

/* !Parse_Color
 * \brief read an xml node which is a color, it must have r, g, and b tags in it
 */
void Parse_Color(xmlNodePtr color, Color_t dst) {
    dst[3] = 255; /* default alpha value of 255 */

    xmlNodePtr cur;
    for (cur = color->children; cur; cur = cur->next) {
	if (!xmlStrcmp(cur->name, (const xmlChar *) "r"))
	    dst[0] = GRAB_INT(cur); 
	else if (!xmlStrcmp(cur->name, (const xmlChar *) "g"))
	    dst[1] = GRAB_INT(cur);
	else if (!xmlStrcmp(cur->name, (const xmlChar *) "b"))
	    dst[2] = GRAB_INT(cur); 
	else if (!xmlStrcmp(cur->name, (const xmlChar *) "a"))
	    dst[3] = GRAB_INT(cur); 
	else
	    BAD_TAG(cur);
    }
}

/* !Parse_Quat
 * \brief read an xml node which is a quaternion, it must have 1, i, j, k values
 */
void Parse_Quat(xmlNodePtr quat, Quatf_t dst) {
    assert(0);
}

/* !Parse_File
 * \brief read in an xml scene file and return a Scene_t struct with the values filled in
 */
Scene_t *Parse_File(const char *fname) {
    xmlDocPtr doc;
    xmlNodePtr cur1, cur2, cur3; /* cursors for stepping through the tree */
    xmlNodePtr root;

    doc = xmlParseFile(fname);
    assert(doc);

    root = xmlDocGetRootElement(doc);
    assert(root);

    /* make sure we have a scene */
    assert(!xmlStrcmp(root->name, (const xmlChar *) "scene"));

    int nLights = 0, nGeo = 0; /* count the lights and geometry objects in the scene */

    for (cur1 = root->children; cur1; cur1 = cur1->next) {
	if (!xmlStrcmp(cur1->name, (const xmlChar *) "light"))
	    nLights++;
	else if (!xmlStrcmp(cur1->name, (const xmlChar *) "geometry"))
	    nGeo++;
    }

    /* allocate the scene file */
    Scene_t *scene = New_Scene(nGeo, nLights);

    /* now we use these as indices into the array */
    nLights = -1;
    nGeo = -1;

    for (cur1 = root->children; cur1; cur1 = cur1->next) {
	if (!xmlStrcmp(cur1->name, (const xmlChar *) "geometry")) {
	    scene->geometry[++nGeo] = NEW(Geometry_t);
	    for (cur2 = cur1->children; cur2; cur2 = cur2->next) {
		if(!xmlStrcmp(cur2->name, (const xmlChar *) "sphere")) {
		    scene->geometry[nGeo]->primitive = (Primitive_t *) NEW(Geo_Sphere_t);
		    for (cur3 = cur2->children; cur3; cur3 = cur3->next) {
			if(!xmlStrcmp(cur3->name, (const xmlChar *) "radius")) {
			    scene->geometry[nGeo]->primitive->sphere.radius = GRAB_FLOAT(cur3);
			} else {
			    BAD_TAG(cur3);
			}
		    }
		} else if(!xmlStrcmp(cur2->name, (const xmlChar *) "box")) {
		} else if(!xmlStrcmp(cur2->name, (const xmlChar *) "torus")) {
		} else if(!xmlStrcmp(cur2->name, (const xmlChar *) "translation")) {
		    Parse_Position(cur2, scene->geometry[nGeo]->trans);
		} else if(!xmlStrcmp(cur2->name, (const xmlChar *) "rotation")) {
		    Parse_Quat(cur2, scene->geometry[nGeo]->rot);
		} else if(!xmlStrcmp(cur2->name, (const xmlChar *) "material")) {
		    scene->geometry[nGeo]->material = NEW(Material_t);
		    for(cur3 = cur2->children; cur3; cur3 = cur3->next) {
			if(!xmlStrcmp(cur3->name, (const xmlChar *) "diffuse_color")) {
			    Parse_Color(cur3, scene->geometry[nGeo]->material->diffuse_color);
			} else if(!xmlStrcmp(cur3->name, (const xmlChar *) "specular_color")) {
			    Parse_Color(cur3, scene->geometry[nGeo]->material->spec_color);
			} else if(!xmlStrcmp(cur3->name, (const xmlChar *) "spec")) {
			    scene->geometry[nGeo]->material->spec = GRAB_FLOAT(cur3);
			} else if(!xmlStrcmp(cur3->name, (const xmlChar *) "glossiness")) {
			    scene->geometry[nGeo]->material->glossiness = GRAB_FLOAT(cur3);
			} else if(!xmlStrcmp(cur3->name, (const xmlChar *) "transperancy")) {
			    scene->geometry[nGeo]->material->transperancy = GRAB_FLOAT(cur3);
			} else if(!xmlStrcmp(cur3->name, (const xmlChar *) "reflection")) {
			    scene->geometry[nGeo]->material->reflection = GRAB_FLOAT(cur3);
			} else {
			    BAD_TAG(cur3);
			}

		    }
		}
	    }
	} else if (!xmlStrcmp(cur1->name, (const xmlChar *) "light")) {
	    scene->light[++nLights] = NEW(Light_t);
	    for (cur2 = cur1->children; cur2; cur2 = cur2->next) {
		if(!xmlStrcmp(cur2->name, (const xmlChar *) "color")) {
		    Parse_Color(cur2, scene->light[nLights]->color);
		} else if(!xmlStrcmp(cur2->name, (const xmlChar *) "intensity")) {
		    scene->light[nLights]->intensity = GRAB_FLOAT(cur2);
		} else if(!xmlStrcmp(cur2->name, (const xmlChar *) "pos")) {
		    Parse_Position(cur2, scene->light[nLights]->pos);
		} else if(!xmlStrcmp(cur2->name, (const xmlChar *) "look_at")) {
		    Parse_Position(cur2, scene->light[nLights]->look_at);
		} else {
		    BAD_TAG(cur2);
		}
	    }
	} else if (!xmlStrcmp(cur1->name, (const xmlChar *) "camera")) {
	    for (cur2 = cur1->children; cur2; cur2 = cur2->next) {
		if(!xmlStrcmp(cur2->name, (const xmlChar *) "pos")) {
		    Parse_Position(cur2, scene->camera->pos);
		} else if(!xmlStrcmp(cur2->name, (const xmlChar *) "look_at")) {
		    Parse_Position(cur2, scene->camera->look_at);
		} else if(!xmlStrcmp(cur2->name, (const xmlChar *) "up")) {
		    Parse_Position(cur2, scene->camera->up);
		} else if(!xmlStrcmp(cur2->name, (const xmlChar *) "focal_length")) {
		    scene->camera->focal_length = GRAB_FLOAT(cur2);
		} else if(!xmlStrcmp(cur2->name, (const xmlChar *) "width")) {
		    scene->camera->width = GRAB_FLOAT(cur2);
		} else if(!xmlStrcmp(cur2->name, (const xmlChar *) "height")) {
		    scene->camera->height = GRAB_FLOAT(cur2);
		} else {
		    BAD_TAG(cur2);
		}
	    }
	} else if (!xmlStrcmp(cur1->name, (const xmlChar *) "settings")) {
	     for (cur2 = cur1->children; cur2; cur2 = cur2->next) {
		if(!xmlStrcmp(cur2->name, (const xmlChar *) "bg_color")) {
		    Parse_Color(cur2, scene->settings->background);
		} else {
		    BAD_TAG(cur2);
		}
	     }
	} else {
	    BAD_TAG(cur1);
	}
    }

    return scene;
}
