#include <iostream>
#include <cstring>

#include "disk/disk.h"
#include "disk_page/page.h"

int main () {
    {
        hybridfs::Disk* disk = new hybridfs::Disk("sim_disk_1", 0, 256, false);

        hybridfs::Page* clean_p = new hybridfs::Page();
        hybridfs::Page* dirty_p = new hybridfs::Page();
        clean_p->ResetMemory();
        dirty_p->ResetMemory();
        memset(dirty_p->GetData(), 1, 300);
        memset(dirty_p->GetData() + 300, 2, 300);

        for (size_t i = 0; i < 256; i++) {
            hybridfs::Page* page = disk->ReadPage(i);
            if (strcmp(clean_p->GetData(), page->GetData())) {
                std::cout << "error exists" << std::endl;
                return 1;
            }
            disk->PutBackPage(i, page);
        }

        for (size_t i = 100; i < 200; i++) {
            hybridfs::Page* page = disk->ReadPage(i);
            page->MarkDirty();
            memcpy(page->GetData(), dirty_p->GetData(), 600);
            disk->PutBackPage(i, page);
        }

        for (size_t i = 0; i < 100; i++) {
            hybridfs::Page* page = disk->ReadPage(i);
            if (strcmp(clean_p->GetData(), page->GetData())) {
                std::cout << "error exists" << std::endl;
                return 1;
            }
            disk->PutBackPage(i, page);
        }

        for (size_t i = 100; i < 200; i++) {
            hybridfs::Page* page = disk->ReadPage(i);
            if (strcmp(dirty_p->GetData(), page->GetData())) {
                std::cout << "error exists" << std::endl;
                return 1;
            }
            disk->PutBackPage(i, page);
        }

        for (size_t i = 200; i < 256; i++) {
            hybridfs::Page* page = disk->ReadPage(i);
            if (strcmp(clean_p->GetData(), page->GetData())) {
                std::cout << "error exists" << std::endl;
                return 1;
            }
            disk->PutBackPage(i, page);
        }
    }

    {
        hybridfs::Disk* disk = new hybridfs::Disk("sim_disk_2", 0, 256, true, 20);

        hybridfs::Page* p = new hybridfs::Page();
        p->ResetMemory();
        memset(p->GetData(), 1, 300);
        memset(p->GetData() + 300, 2, 300);

        for (size_t i = 0; i < 256; i++) {
            hybridfs::Page* page = disk->ReadPage(i);
            page->MarkDirty();
            memcpy(page->GetData(), p->GetData(), 600);
            disk->PutBackPage(i, page);
        }

        disk->Flush();
        
        for (size_t i = 0; i < 256; i++) {
            hybridfs::Page* page = disk->ReadPage(i);
            if (strcmp(p->GetData(), page->GetData())) {
                std::cout << "error exists" << std::endl;
                return 1;
            }
            disk->PutBackPage(i, page);
        }

        disk->Flush();
    
        for (size_t i = 0; i < 256; i++) {
            hybridfs::Page* page = disk->ReadPage(i);
            if (strcmp(p->GetData(), page->GetData())) {
                std::cout << "error exists" << std::endl;
                return 1;
            }
            disk->PutBackPage(i, page);
        }
    }
    
    return 0;
}