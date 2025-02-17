#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Device structure
typedef struct // TOTAL SIZE: 1000 bytes memory
{
  char nama_produk[200];
  char tahun_rilis[20];
  char cpu[300];
  char kapasitas_baterai[30];
  char ram[30];
  char memori_internal[30];
  char kamera_utama[30];
  char kamera_selfie[30];
  char resolusi[30];
  char tipe_layar[100];
  char operasi_sistem[200];
} Device;

// Function to allocate memory for devices
Device *allocateDevices(int *max) // TOTAL SIZE: 15,125,000 bytes memory [14.7MB] (3.025.000 * 5 devices)
{
  Device *devices = (Device *)malloc((*max) * sizeof(Device));
  if (devices == NULL)
  {
    printf("Failed to allocate memory.\n");
    exit(1); // Exit program if memory allocation fails
  }
  return devices;
}

// Function to read devices from a CSV file
int readDevices(const char *filename, Device devices[], int maxDevices)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Failed to open file: %s\n", filename);
    exit(1); // Indicate failure
  }

  char buffer[1024];
  int count = 0;

  // Skip the header line
  fgets(buffer, sizeof(buffer), file);

  // Read and parse each line
  while (fgets(buffer, sizeof(buffer), file))
  {
    if (count >= maxDevices)
      break; // Prevent exceeding the array size

    sscanf(buffer,
           "%199[^,],%19[^,],%299[^,],%29[^,],%29[^,],%29[^,],%29[^,],%29[^,],%29[^,],%99[^,],%199[^\n]",
           devices[count].nama_produk,
           devices[count].tahun_rilis,
           devices[count].cpu,
           devices[count].kapasitas_baterai,
           devices[count].ram,
           devices[count].memori_internal,
           devices[count].kamera_utama,
           devices[count].kamera_selfie,
           devices[count].resolusi,
           devices[count].tipe_layar,
           devices[count].operasi_sistem);
    count++;
  }

  fclose(file);
  return count; // Return the number of devices read
}

// Function to read devices from a CSV file
void loadDevices(Device SonyDevices[], int *SonyCount,
                 Device AppleDevices[], int *AppleCount,
                 Device VivoDevices[], int *VivoCount,
                 Device XiaomiDevices[], int *XiaomiCount,
                 Device SamsungDevices[], int *SamsungCount, int *maxDevices)
{

  // Load Sony devices
  *SonyCount = readDevices("Sony.csv", SonyDevices, *maxDevices);
  if (*SonyCount < 0)
  {
    printf("Error reading Sony devices\n");
    exit(1); // Exit if reading Sony.csv failed
  }

  // Load Apple devices
  *AppleCount = readDevices("Apple.csv", AppleDevices, *maxDevices);
  if (*AppleCount < 0)
  {
    printf("Error reading Apple devices\n");
    exit(1); // Exit if reading Apple.csv failed
  }

  // Load Vivo devices
  *VivoCount = readDevices("Vivo.csv", VivoDevices, *maxDevices);
  if (*VivoCount < 0)
  {
    printf("Error reading Vivo devices\n");
    exit(1); // Exit if reading Vivo.csv failed
  }

  // Load Xiaomi devices
  *XiaomiCount = readDevices("Xiaomi.csv", XiaomiDevices, *maxDevices);
  if (*XiaomiCount < 0)
  {
    printf("Error reading Xiaomi devices\n");
    exit(1); // Exit if reading Xiaomi.csv failed
  }

  // Load Samsung devices
  *SamsungCount = readDevices("Samsung.csv", SamsungDevices, *maxDevices);
  if (*SamsungCount < 0)
  {
    printf("Error reading Samsung devices\n");
    exit(1); // Exit if reading Samsung.csv failed
  }
}

// Function to print a single Device
void printDevice(Device device)
{
  printf("Nama Produk: \t\t%s\n", device.nama_produk);
  printf("Tahun Rilis: \t\t%s\n", device.tahun_rilis);
  printf("CPU: \t\t\t%s\n", device.cpu);
  printf("Kapasitas Baterai: \t%s\n", device.kapasitas_baterai);
  printf("RAM: \t\t\t%s\n", device.ram);
  printf("Memori Internal: \t%s\n", device.memori_internal);
  printf("Kamera Utama: \t\t%s\n", device.kamera_utama);
  printf("Kamera Selfie: \t\t%s\n", device.kamera_selfie);
  printf("Resolusi: \t\t%s\n", device.resolusi);
  printf("Tipe Layar: \t\t%s\n", device.tipe_layar);
  printf("Operasi Sistem: \t%s\n", device.operasi_sistem);
  printf("\n");
}

// Menu for viewing devices
void viewDevicesMenu(Device SonyDevices[], int SonyCount,
                     Device AppleDevices[], int AppleCount,
                     Device VivoDevices[], int VivoCount,
                     Device XiaomiDevices[], int XiaomiCount,
                     Device SamsungDevices[], int SamsungCount)
{
  char choice[1024];
  int field = 0;
  do
  {
    printf("\n=== View Devices Menu ===\n");
    printf("1. Tampilkan perangkat Sony\n");
    printf("2. Tampilkan perangkat Apple\n");
    printf("3. Tampilkan perangkat Vivo\n");
    printf("4. Tampilkan perangkat Xiaomi\n");
    printf("5. Tampilkan perangkat Samsung\n");
    printf("6. Kembali ke Menu Utama\n");
    printf("Pilih opsi: ");
    // Use fgets to read input (it handles spaces and newlines well)
    fgets(choice, sizeof(choice), stdin);
    // Remove any newline character from the input that fgets might have read
    choice[strcspn(choice, "\n")] = '\0';
    field = atoi(choice);

    if (field >= 1 && field <= 6)
    {
      switch (field)
      {
      case 1:
        printf("\n=== Sony Devices ===\n");
        for (int i = 0; i < SonyCount; i++)
          printDevice(SonyDevices[i]);
        break;

      case 2:
        printf("\n=== Apple Devices ===\n");
        for (int i = 0; i < AppleCount; i++)
          printDevice(AppleDevices[i]);
        break;

      case 3:
        printf("\n=== Vivo Devices ===\n");
        for (int i = 0; i < VivoCount; i++)
          printDevice(VivoDevices[i]);
        break;

      case 4:
        printf("\n=== Xiaomi Devices ===\n");
        for (int i = 0; i < XiaomiCount; i++)
          printDevice(XiaomiDevices[i]);
        break;

      case 5:
        printf("\n=== Samsung Devices ===\n");
        for (int i = 0; i < SamsungCount; i++)
          printDevice(SamsungDevices[i]);
        break;

      case 6:
        printf("Kembali ke Menu Utama.\n");
        break;
      }
    }
    else
    {
      printf("Pilihan tidak valid. Coba lagi.\n");
    }
  } while (field != 6);
}

// Function to search for a device
void searching(Device SonyDevices[], int SonyCount,
               Device AppleDevices[], int AppleCount,
               Device VivoDevices[], int VivoCount,
               Device XiaomiDevices[], int XiaomiCount,
               Device SamsungDevices[], int SamsungCount,
               char *query, int field)
{
  int found = 0;

  // Loop through each array of devices: Sony, Apple, Vivo, Xiaomi, Samsung
  Device *allDevices[] = {SonyDevices, AppleDevices, VivoDevices, XiaomiDevices, SamsungDevices};
  int allCounts[] = {SonyCount, AppleCount, VivoCount, XiaomiCount, SamsungCount};

  for (int j = 0; j < 5; j++)
  { // There are 5 device arrays (Sony, Apple, Vivo, Xiaomi, Samsung)
    Device *devices = allDevices[j];
    int count = allCounts[j];

    for (int i = 0; i < count; i++)
    { // Loop through each device in the current array
      char *targetField;

      // Determine the field based on the 'field' parameter
      switch (field)
      {
      case 1:
        targetField = devices[i].nama_produk;
        break;
      case 2:
        targetField = devices[i].tahun_rilis;
        break;
      case 3:
        targetField = devices[i].cpu;
        break;
      case 4:
        targetField = devices[i].kapasitas_baterai;
        break;
      case 5:
        targetField = devices[i].ram;
        break;
      case 6:
        targetField = devices[i].memori_internal;
        break;
      case 7:
        targetField = devices[i].kamera_utama;
        break;
      case 8:
        targetField = devices[i].kamera_selfie;
        break;
      case 9:
        targetField = devices[i].resolusi;
        break;
      case 10:
        targetField = devices[i].tipe_layar;
        break;
      case 11:
        targetField = devices[i].operasi_sistem;
        break;
      default:
        return;
      }

      // Check if the target field contains the query
      if (strstr(targetField, query))
      {
        printDevice(devices[i]); // Print the device if it matches
        found = 1;
      }
    }
  }

  // If no matching devices were found
  if (found == 0)
  {
    printf("Tidak ada dalam pencarian.\n");
  }
}

// Function to search for a device (placeholder for now)
void searchDevice(Device SonyDevices[], int SonyCount,
                  Device AppleDevices[], int AppleCount,
                  Device VivoDevices[], int VivoCount,
                  Device XiaomiDevices[], int XiaomiCount,
                  Device SamsungDevices[], int SamsungCount)
{
  char choice[1000];
  char query[1000];
  int field = 0;
  do
  {
    printf("\n=== Search Device ===\n");
    printf("1. Mencari Nama Produk\n");
    printf("2. Mencari Tahun Rilis\n");
    printf("3. Mencari CPU\n");
    printf("4. Mencari Kapasitas Baterai\n");
    printf("5. Mencari RAM\n");
    printf("6. Mencari Memori Internal\n");
    printf("7. Mencari Kamera Utama\n");
    printf("8. Mencari Kamera Selfie\n");
    printf("9. Mencari Resolusi\n");
    printf("10. Mencari Tipe Layar\n");
    printf("11. Mencari Operasi Sistem\n");
    printf("12. Kembali ke Menu Utama\n");
    printf("Pilih opsi: ");
    // Use fgets to read input (it handles spaces and newlines well)
    fgets(choice, sizeof(choice), stdin);
    // Remove any newline character from the input that fgets might have read
    choice[strcspn(choice, "\n")] = '\0';
    field = atoi(choice);

    if (field >= 1 && field <= 11)
    {
      printf("Masukkan kata kunci pencarian: ");
      fgets(query, sizeof(query), stdin);
      query[strcspn(query, "\n")] = '\0';

      printf("\nHasil pencarian untuk '%s'\n", query);
      searching(SonyDevices, SonyCount,
                AppleDevices, AppleCount,
                VivoDevices, VivoCount,
                XiaomiDevices, XiaomiCount,
                SamsungDevices, SamsungCount, query, field);
    }

    else if (field == 12)
    {
      printf("Kembali ke Menu Utama.\n");
    }

    else
    {
      printf("Pilihan tidak valid. Coba lagi.\n");
    }
  } while (field != 12);
}

// Function to add a device (placeholder for now)
void addDevice(const char *filename)
{
  Device newDevice;
  FILE *file = fopen(filename, "a"); // Open file in append mode
  if (file == NULL)
  {
    printf("Failed to open file: %s\n", filename);
    exit(1);
  }

  printf("\n=== Tambah Device Baru ===\n");
  int size = 1000;
  // Get device details from the user
  printf("Masukkan Nama Produk: ");
  fgets(newDevice.nama_produk, size, stdin);
  newDevice.nama_produk[strcspn(newDevice.nama_produk, "\n")] = '\0';

  printf("Masukkan Tahun Rilis: ");
  fgets(newDevice.tahun_rilis, size, stdin);
  newDevice.tahun_rilis[strcspn(newDevice.tahun_rilis, "\n")] = '\0';

  printf("Masukkan CPU: ");
  fgets(newDevice.cpu, size, stdin);
  newDevice.cpu[strcspn(newDevice.cpu, "\n")] = '\0';

  printf("Masukkan Kapasitas Baterai: ");
  fgets(newDevice.kapasitas_baterai, size, stdin);
  newDevice.kapasitas_baterai[strcspn(newDevice.kapasitas_baterai, "\n")] = '\0';

  printf("Masukkan RAM: ");
  fgets(newDevice.ram, size, stdin);
  newDevice.ram[strcspn(newDevice.ram, "\n")] = '\0';

  printf("Masukkan Memori Internal: ");
  fgets(newDevice.memori_internal, size, stdin);
  newDevice.memori_internal[strcspn(newDevice.memori_internal, "\n")] = '\0';

  printf("Masukkan Kamera Utama: ");
  fgets(newDevice.kamera_utama, size, stdin);
  newDevice.kamera_utama[strcspn(newDevice.kamera_utama, "\n")] = '\0';

  printf("Masukkan Kamera Selfie: ");
  fgets(newDevice.kamera_selfie, size, stdin);
  newDevice.kamera_selfie[strcspn(newDevice.kamera_selfie, "\n")] = '\0';

  printf("Masukkan Resolusi: ");
  fgets(newDevice.resolusi, size, stdin);
  newDevice.resolusi[strcspn(newDevice.resolusi, "\n")] = '\0';

  printf("Masukkan Tipe Layar: ");
  fgets(newDevice.tipe_layar, size, stdin);
  newDevice.tipe_layar[strcspn(newDevice.tipe_layar, "\n")] = '\0';

  printf("Masukkan Sistem Operasi: ");
  fgets(newDevice.operasi_sistem, size, stdin);
  newDevice.operasi_sistem[strcspn(newDevice.operasi_sistem, "\n")] = '\0';

  // Write the new device to the file in CSV format
  fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
          newDevice.nama_produk,
          newDevice.tahun_rilis,
          newDevice.cpu,
          newDevice.kapasitas_baterai,
          newDevice.ram,
          newDevice.memori_internal,
          newDevice.kamera_utama,
          newDevice.kamera_selfie,
          newDevice.resolusi,
          newDevice.tipe_layar,
          newDevice.operasi_sistem);

  printf("\nDevice baru berhasil ditambahkan ke file '%s'.\n", filename);

  fclose(file); // Close the file
}

int main()
{
  int maxDevices = 3024;

  // Dynamically allocate memory for each brand
  Device *SonyDevices = allocateDevices(&maxDevices);
  Device *AppleDevices = allocateDevices(&maxDevices);
  Device *VivoDevices = allocateDevices(&maxDevices);
  Device *XiaomiDevices = allocateDevices(&maxDevices);
  Device *SamsungDevices = allocateDevices(&maxDevices);

  int SonyCount, AppleCount, VivoCount, XiaomiCount, SamsungCount;
  SonyCount = AppleCount = VivoCount = XiaomiCount = SamsungCount = 0;

  loadDevices(SonyDevices, &SonyCount, AppleDevices, &AppleCount, VivoDevices, &VivoCount,
              XiaomiDevices, &XiaomiCount, SamsungDevices, &SamsungCount, &maxDevices);

  char mainChoice[1000]; // Use a buffer to hold user input
  int field = 0;
  do
  {
    printf("\n=== Main Menu ===\n");
    printf("1. View Devices\n");
    printf("2. Searching\n");
    printf("3. Add Device\n");
    printf("4. Exit\n");
    printf("Pilih opsi: ");
    // intinya bisa membaca inputan yang mengandung spasi dan newline
    fgets(mainChoice, sizeof(mainChoice), stdin);
    // menghilangkan newline karena fgets diakhiri dengan /n
    mainChoice[strcspn(mainChoice, "\n")] = '\0';
    field = atoi(mainChoice);

    // Check if input is a single digit and valid
    if (field >= 1 && field <= 4)
    {
      switch (field)
      {
      case 1:
        viewDevicesMenu(SonyDevices, SonyCount,
                        AppleDevices, AppleCount,
                        VivoDevices, VivoCount,
                        XiaomiDevices, XiaomiCount,
                        SamsungDevices, SamsungCount);
        break;

      case 2:
        searchDevice(SonyDevices, SonyCount,
                     AppleDevices, AppleCount,
                     VivoDevices, VivoCount,
                     XiaomiDevices, XiaomiCount,
                     SamsungDevices, SamsungCount);
        break;

      case 3:
        printf("\n=== Tambah Perangkat Baru ===\n");
        printf("Masukkan nama file untuk menyimpan perangkat (contoh: NewDevices.csv): ");
        char newFile[1000];
        // fgets bisa membaca inputan yang mengandung spasi dan newline
        fgets(newFile, sizeof(newFile), stdin);
        // menghilangkan newline karena fgets diakhiri dengan /n
        newFile[strcspn(newFile, "\n")] = '\0';
        addDevice(newFile);
        break;

      case 4:
        printf("Keluar dari program. Terima kasih!\n");
        break;
      }
    }
    else
    {
      printf("Pilihan tidak valid. Coba lagi.\n");
    }
  } while (field != 4);

  // Free dynamically allocated memory before exiting
  free(SonyDevices);
  free(AppleDevices);
  free(VivoDevices);
  free(XiaomiDevices);
  free(SamsungDevices);

  return 0;
}