
#include "delivery.h"

Delivery *build_delivery(FILE *pf);

int main(int argc, char const *argv[])
{
    Delivery* a;
    FILE *f;
    f = fopen("requests.txt", "r");
    if (!(a = build_delivery(f)))
    {
        return -1;
    }
    fclose(f);

    delivery_free(a);
    
    return 0;
}

/**
 * @brief Builds a delivery from the information read on the file.
 *
 * @param pf File descriptor. The file should contain the following information:
 * First line: delivery_name product_name
 * Second line: number of cities/vertices
 * Following lines: vertices description
 *
 * @return A pointer to the fulfilled delivery. If there have been errors
returns NULL.
 */
Delivery *build_delivery(FILE *pf)
{
    Delivery *d = NULL;
    char name[30] = "";
    char vacuna[30] = "";
    char str[30] = "";
    int i, cantidad = 0;
    if (!pf)
    {
        return NULL;
    }

    fscanf(pf, "%s %s", name, vacuna);
    d = delivery_init(name, vacuna);
    
    fscanf(pf, "%i", &cantidad);
    fgetc(pf);
    for (i = 0; i < cantidad; i++)
    {
        fgets(str, 30, pf);
        delivery_add(stdout, d, (void *)vertex_initFromString(str), vertex_print);
        printf("\n");
    }

        delivery_run_plan(stdout, d, vertex_print, vertex_free);

    return d;
}