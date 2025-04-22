#include "vertex.h"
#include <string.h>

#include "vertex.h"

Vertex *vertex_init()
{
    Vertex *x = NULL;

    if (!(x = malloc(sizeof(Vertex))))
        return NULL;
    
    x->id = -1;
    x->state = WHITE;
    x->tag[0] = '\0';

    return x;
}
/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/

void vertex_free(void *v)
{
    free((Vertex *)v);
}

long vertex_getId(const Vertex *v)
{
    return v->id;
}

const char *vertex_getTag(const Vertex *v)
{
    return v->tag;
}

Label vertex_getState(const Vertex *v)
{
    return v->state;
}

int vertex_getIndex(const Vertex *v)
{
    return v->index;
}

Status vertex_setId(Vertex *v, const long id)
{
    if (!(v->id = id))
        return ERROR;
    return OK;
}

Status vertex_setTag(Vertex *v, const char *tag)
{
    if (!(strcpy(v->tag, tag)))
        return ERROR;
    return OK;
}

Status vertex_setState(Vertex *v, const Label state)
{
    if (!(v->state = state))
        return ERROR;
    return OK;
}



int vertex_cmp(const void *v1, const void *v2)
{
    Vertex *vx1 = (Vertex *)v1, *vx2 = (Vertex *)v2;

    if (vx1->id > vx2->id)
    {
        return 1;
    }
    else if (vx1->id < vx2->id)
    {
        return -1;
    }
    else
    {
        return strcmp(vx1->tag, vx2->tag);
    }
    return 0;
}

void *vertex_copy(const void *src)
{
    Vertex *v = vertex_init(), *x = (Vertex *)src;

    v->id = x->id;

    strcpy(v->tag, x->tag);

    v->state = x->state;

    return v;
}

int vertex_print(FILE *pf, const void *v)
{
    Vertex *ver = (Vertex *)v;

    if (!ver || !pf)return -1;
        
    
    return fprintf(pf, "[%ld, %s, %u, %i]", vertex_getId(ver), vertex_getTag(ver), vertex_getState(ver), vertex_getIndex(ver));

}

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/
Status vertex_setField (Vertex *v, char *key, char *value);

Status vertex_setField (Vertex *v, char *key, char *value) {
  if (!key || !value) return ERROR;

  if (strcmp(key, "id") == 0) {
    return vertex_setId(v, atol(value));
  } else if (strcmp(key, "tag") == 0) {
    return vertex_setTag(v, value);
  } else if (strcmp(key, "state") == 0) {
    return vertex_setState(v, (Label)atoi(value));
  }

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/
Vertex *vertex_initFromString(char *descr){
  char buffer[1024];
  char *token;
  char *key;
  char *value = '\0';
  char *p;
  Vertex *v;

  /* Check args: */
  if (!descr) return NULL;

  /* Allocate memory for vertex: */
  v = vertex_init();
  if (!v) return NULL;

  /* Read and tokenize description: */
  sprintf(buffer, "%s", descr);
  token = strtok(buffer, " \t\n");
  while (token) {
    p = strchr(token, ':');
    if (!p) continue;

    *p = '\0';
    key = token;
    value = p+1;

    vertex_setField(v, key, value);

    token = strtok(NULL, " \t\n");
  }

  return v;
}

/**  rest of the functions in vertex.h **/
