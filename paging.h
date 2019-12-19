#ifndef PAGING_H
#define PAGING_H

#include "list.h"

struct list page_info_list;

struct page_info {
    struct list_elem elem;
    char p_name[128];
    int pid;
    int last_access_time;

    struct swap_info *s_info;
};

struct swap_info {
    int evict_time;
    int reinsert_time;
    struct page_info *p_info;
};

void handle_pgfault();
pte_t* select_a_victim(pde_t *pgdir);
void clearaccessbit(pde_t *pgdir);
int getswappedblk(pde_t *pgdir, uint va);
int swap_page(pde_t *pgdir);
void swap_page_from_pte(pte_t *pte);
void map_address(pde_t *pgdir, uint addr);
pte_t *uva2pte(pde_t *pgdir, uint uva);

#endif
