#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <sys/utsname.h>
#include <unistd.h>

#define COLOR_RESET "\x1b[0m"
#define COLOR_GOLD "\x1b[38;2;218;165;32m" // Goldenrod
#define COLOR_WHITE "\x1b[1;97m"
#define COLOR_GRAY "\x1b[90m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_PURPLE "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define MAX_LINE_LEN 512

const char *ascii_art_arch[] = {"                  -`",
                                "                 .o+`",
                                "                `ooo/",
                                "               `+oooo:",
                                "              `+oooooo:",
                                "              -+oooooo+:",
                                "            `/:-:++oooo+:",
                                "           `/++++/+++++++:",
                                "          `/++++++++++++++:",
                                "         `/+++ooooooooooooo/`",
                                "        ./ooosssso++osssssso+`",
                                "       .oossssso-````/ossssss+`",
                                "      -osssssso.      :ssssssso.",
                                "     :osssssss/        osssso+++.",
                                "    /ossssssss/        +ssssooo/-",
                                "  `/ossssso+/:-        -:/+osssso+-",
                                " `+sso+:-`                 `.-/+oso:",
                                "`++:.                           `-/+/",
                                ".`                                 `/"};
const int ascii_height_arch = 19;
const int ascii_width_arch = 37;

const char *ascii_art_tux[] = {
    "        #####",          "       #######",         "       ##O#O##",
    "       #######",         "     ##..###..##",       "    #..........##",
    "   #............##",     "   #............###",    "  ##.#..........##.#",
    "######.#######.#######", "#######.#####.########", "  #################"};
const int ascii_height_tux = 12;
const int ascii_width_tux = 30;

const char *ascii_art_ubuntu[] = {"                         ./+o+-",
                                  "                 yyyyy- -yyyyyy+",
                                  "              ://+//////-yyyyyyo",
                                  "          .++ .:/++++++/-.+sss/`",
                                  "        .:++o:  /++++++++/:--:/-",
                                  "       o:+o+:++.`..```.-/oo+++++/",
                                  "      .:+o:+o/.          `+sssoo+/",
                                  " .++/+:+oo+o:`             /sssooo.",
                                  "/+++//+:`oo+o               /::--:.",
                                  "+/+o+++`o++o               ++////.",
                                  " .++.o+++oo+:`             /dddhhh.",
                                  "      .+.o+oo:.          `oddhhhh+",
                                  "       +.++o+o`-````.:ohdhhhhh+",
                                  "        `:o+++ `ohhhhhhhhyo++os:",
                                  "          .o:`.syhhhhhhh/.oo++o`",
                                  "              /osyyyyyyo++ooo+++/",
                                  "                  ````` +oo+++o:",
                                  "                         `oo++."};
const int ascii_height_ubuntu = 18;
const int ascii_width_ubuntu = 38;

const char *ascii_art_debian[] = {"       _,met$$$$$$$$$$gg.",
                                  "    ,g$$$$$$$$$$$$$$$$$$$$P.",
                                  "  ,g$$$$P\"\"       \"\"\"Y$$$$.\".",
                                  " ,$$$$P'              `$$$$$$.",
                                  "',$$$$P       ,ggs.     `$$$$b:",
                                  "`d$$$$'     ,$P\"'   .    $$$$$$",
                                  " $$$$P      d$'     ,    $$$$P",
                                  " $$$$:      $$$.   -    ,d$$$$'",
                                  " $$$$;      Y$b._   _,d$P'",
                                  " Y$$$$.    `.`\"Y$$$$$$$$P\"'",
                                  " `$$$$b      \"-.__",
                                  "  `Y$$$$b",
                                  "   `Y$$$$.",
                                  "     `$$$$b.",
                                  "       `Y$$$$b.",
                                  "         `\"Y$$b._",
                                  "             `\"\"\"\""};
const int ascii_height_debian = 17;
const int ascii_width_debian = 40;

const char *ascii_art_fedora[] = {"             .',;::::;,'.",
                                  "         .';:cccccccccccc:;,.",
                                  "      .;cccccccccccccccccccccc;.",
                                  "    .:cccccccccccccccccccccccccc:.",
                                  "  .;ccccccccccccc;.:dddl:.;ccccccc;.",
                                  " .:ccccccccccccc;OWMKOOXMWd;ccccccc:.",
                                  ".:ccccccccccccc;KMMc;cc;xMMc;ccccccc:.",
                                  ",cccccccccccccc;MMM.;cc;;WW:;cccccccc,",
                                  ":cccccccccccccc;MMM.;cccccccccccccccc:",
                                  ":ccccccc;oxOOOo;MMM000k.;cccccccccccc:",
                                  "cccccc;0MMKxdd:;MMMkddc.;cccccccccccc;",
                                  "ccccc;XMO';cccc;MMM.;cccccccccccccccc'",
                                  "ccccc;MMo;ccccc;MMW.;ccccccccccccccc;",
                                  "ccccc;0MNc.ccc.xMMd;ccccccccccccccc;",
                                  "cccccc;dNMWXXXWM0:;cccccccccccccc:,",
                                  "cccccccc;.:odl:.;cccccccccccccc:,.",
                                  "ccccccccccccccccccccccccccccc:'.",
                                  ":ccccccccccccccccccccccc:;,..",
                                  " ':cccccccccccccccc::;,."};
const int ascii_height_fedora = 19;
const int ascii_width_fedora = 38;

void trim_newline(char *str) {
  int len = strlen(str);
  while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == ' ' ||
                     str[len - 1] == '\r')) {
    str[len - 1] = '\0';
    len--;
  }
}

/* Decode UTF-8 sequence starting at str[i], advance i past it, return codepoint
 */
static unsigned long decode_utf8(const char *str, int *i) {
  unsigned char c = (unsigned char)str[*i];
  unsigned long cp = 0;
  int extra = 0;
  if (c < 0x80) {
    cp = c;
  } else if (c < 0xE0) {
    cp = c & 0x1F;
    extra = 1;
  } else if (c < 0xF0) {
    cp = c & 0x0F;
    extra = 2;
  } else {
    cp = c & 0x07;
    extra = 3;
  }
  for (int j = 0; j < extra; j++) {
    (*i)++;
    cp = (cp << 6) | ((unsigned char)str[*i] & 0x3F);
  }
  return cp;
}

/* Returns visible terminal column width of a string (handles ANSI + Nerd Font
 * 2-wide icons) */
int visible_length(const char *str) {
  int len = 0;
  int in_ansi = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == '\x1b') {
      in_ansi = 1;
      continue;
    }
    if (in_ansi) {
      if (str[i] == 'm' || str[i] == 'J')
        in_ansi = 0;
      continue;
    }

    if ((unsigned char)str[i] >= 0x80) {
      unsigned long cp = decode_utf8(str, &i);
      /* CJK and Emojis are 2 columns visually in Alacritty */
      if ((cp >= 0x1F000 && cp <= 0x1F9FF) || /* Emojis */
          (cp >= 0x1100 && cp <= 0x115F) || (cp >= 0x2E80 && cp <= 0x303E) ||
          (cp >= 0x3041 && cp <= 0x33BF) || (cp >= 0xFF01 && cp <= 0xFF60)) {
        len += 2;
      } else {
        /* Nerd Font PUA icons typically advance cursor by 1 column */
        len += 1;
      }
    } else {
      len += 1;
    }
  }
  return len;
}

void get_os_name(char *buffer, size_t size) {
  FILE *f = fopen("/etc/os-release", "r");
  char name[256] = "Unknown Linux";
  if (f) {
    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), f)) {
      if (strncmp(line, "PRETTY_NAME=", 12) == 0) {
        char *start = line + 12;
        if (*start == '"')
          start++;
        trim_newline(start);
        int len = strlen(start);
        if (len > 0 && start[len - 1] == '"')
          start[len - 1] = '\0';
        strncpy(name, start, sizeof(name) - 1);
        break;
      }
    }
    fclose(f);
  }
  /* Append architecture */
  struct utsname un;
  if (uname(&un) == 0) {
    snprintf(buffer, size, "%s %s", name, un.machine);
  } else {
    strncpy(buffer, name, size);
  }
}

void get_uptime(char *buffer, size_t size) {
  FILE *f = fopen("/proc/uptime", "r");
  if (!f) {
    strncpy(buffer, "Unknown", size);
    return;
  }
  double up;
  if (fscanf(f, "%lf", &up) == 1) {
    int seconds = (int)up;
    int mins = (seconds / 60) % 60;
    int hours = (seconds / 3600) % 24;
    int days = seconds / 86400;
    if (days > 0)
      snprintf(buffer, size, "%d day%s, %d hour%s, %d min%s", days,
               days == 1 ? "" : "s", hours, hours == 1 ? "" : "s", mins,
               mins == 1 ? "" : "s");
    else if (hours > 0)
      snprintf(buffer, size, "%d hour%s, %d min%s", hours,
               hours == 1 ? "" : "s", mins, mins == 1 ? "" : "s");
    else
      snprintf(buffer, size, "%d min%s", mins, mins == 1 ? "" : "s");
  } else {
    strncpy(buffer, "Unknown", size);
  }
  fclose(f);
}

void get_memory(char *buffer, size_t size) {
  FILE *f = fopen("/proc/meminfo", "r");
  if (!f) {
    strncpy(buffer, "Unknown", size);
    return;
  }
  long total = 0, available = 0;
  char line[MAX_LINE_LEN];
  while (fgets(line, sizeof(line), f)) {
    if (strncmp(line, "MemTotal:", 9) == 0)
      sscanf(line, "MemTotal: %ld kB", &total);
    else if (strncmp(line, "MemAvailable:", 13) == 0)
      sscanf(line, "MemAvailable: %ld kB", &available);
  }
  fclose(f);
  if (total > 0 && available > 0) {
    long used = total - available;
    int pct = (int)((used * 100.0) / total);
    const char *p_col =
        (pct < 50) ? COLOR_GREEN : ((pct < 80) ? COLOR_YELLOW : COLOR_RED);
    snprintf(buffer, size, "%.2f GiB / %.2f GiB (%s%d%%%s)",
             (double)used / (1024 * 1024), (double)total / (1024 * 1024), p_col,
             pct, COLOR_WHITE);
  } else {
    strncpy(buffer, "Unknown", size);
  }
}

void get_cpu(char *buffer, size_t size) {
  FILE *f = fopen("/proc/cpuinfo", "r");
  if (!f) {
    strncpy(buffer, "Unknown", size);
    return;
  }
  char line[MAX_LINE_LEN];
  char model[256] = "";
  int logical = 0;
  int phys_cores = 0; /* 'cpu cores' field for first socket */
  int got_phys = 0;
  while (fgets(line, sizeof(line), f)) {
    if (strncmp(line, "model name", 10) == 0 && model[0] == '\0') {
      char *p = strchr(line, ':');
      if (p) {
        p++;
        while (*p == ' ')
          p++;
        trim_newline(p);
        strncpy(model, p, sizeof(model) - 1);
        model[sizeof(model) - 1] = '\0';
      }
    }
    if (strncmp(line, "processor", 9) == 0)
      logical++;
    if (strncmp(line, "cpu cores", 9) == 0 && !got_phys) {
      char *p = strchr(line, ':');
      if (p) {
        sscanf(p + 1, " %d", &phys_cores);
        got_phys = 1;
      }
    }
  }
  fclose(f);

  /* Detect P-cores vs E-cores via thread_siblings_list:
     P-cores support Hyper-Threading → siblings list has range "a-b" (count as 2
     logical) E-cores are single-threaded → siblings list is a single number
     (count as 1 logical) We count logical threads per type, matching
     fastfetch's (12+8) format */
  int p_cores = 0, e_cores = 0;
  {
    int seen_cores[1024];
    int seen_count = 0;
    for (int ci = 0; ci < logical; ci++) {
      char path[128];
      snprintf(path, sizeof(path),
               "/sys/devices/system/cpu/cpu%d/topology/thread_siblings_list",
               ci);
      FILE *st = fopen(path, "r");
      if (!st)
        break;
      char sib[64];
      int has_range = 0;
      if (fgets(sib, sizeof(sib), st)) {
        trim_newline(sib);
        has_range = (strchr(sib, '-') != NULL);
      }
      fclose(st);

      /* Deduplicate by physical core_id */
      snprintf(path, sizeof(path),
               "/sys/devices/system/cpu/cpu%d/topology/core_id", ci);
      FILE *cid_f = fopen(path, "r");
      if (!cid_f)
        continue;
      int core_id = -1;
      fscanf(cid_f, "%d", &core_id);
      fclose(cid_f);

      int already = 0;
      for (int s = 0; s < seen_count; s++) {
        if (seen_cores[s] == core_id) {
          already = 1;
          break;
        }
      }
      if (already)
        continue;
      if (seen_count < 1024)
        seen_cores[seen_count++] = core_id;

      /* P-cores have HT → contribute 2 logical threads; E-cores contribute 1 */
      if (has_range)
        p_cores += 2;
      else
        e_cores += 1;
    }
  }

  /* Real max freq: scan all CPUs and take global maximum */
  double freq_ghz = 0.0;
  for (int ci = 0; ci < logical; ci++) {
    char path[128];
    snprintf(path, sizeof(path),
             "/sys/devices/system/cpu/cpu%d/cpufreq/cpuinfo_max_freq", ci);
    FILE *ff = fopen(path, "r");
    if (!ff) {
      snprintf(path, sizeof(path),
               "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_max_freq", ci);
      ff = fopen(path, "r");
    }
    if (ff) {
      long freq;
      if (fscanf(ff, "%ld", &freq) == 1) {
        double ghz = freq / 1000000.0;
        if (ghz > freq_ghz)
          freq_ghz = ghz;
      }
      fclose(ff);
    }
  }

  /* CPU temperature: find coretemp (Intel) or k10temp (AMD) hwmon,
     read temp1_input = Package ID 0, matching fastfetch's behaviour */
  double temp_c = 0.0;
  {
    char path[256];
    for (int h = 0; h < 32 && temp_c == 0.0; h++) {
      snprintf(path, sizeof(path), "/sys/class/hwmon/hwmon%d/name", h);
      FILE *nf = fopen(path, "r");
      if (!nf)
        break;
      char hwname[64] = "";
      if (fgets(hwname, sizeof(hwname), nf))
        trim_newline(hwname);
      fclose(nf);
      /* Match Intel coretemp or AMD k10temp */
      if (strcmp(hwname, "coretemp") == 0 || strcmp(hwname, "k10temp") == 0) {
        snprintf(path, sizeof(path), "/sys/class/hwmon/hwmon%d/temp1_input", h);
        FILE *tf = fopen(path, "r");
        if (tf) {
          long t;
          if (fscanf(tf, "%ld", &t) == 1 && t > 0)
            temp_c = t / 1000.0;
          fclose(tf);
        }
      }
    }
  }

  if (model[0] != '\0') {
    char core_str[32] = "";
    if (p_cores > 0 && e_cores > 0)
      snprintf(core_str, sizeof(core_str), " (%d+%d)", p_cores, e_cores);
    else if (phys_cores > 0)
      snprintf(core_str, sizeof(core_str), " (%d)", phys_cores);

    char freq_str[32] = "";
    if (freq_ghz > 0.0)
      snprintf(freq_str, sizeof(freq_str), " @ %.2f GHz", freq_ghz);

    char temp_str[64] = "";
    if (temp_c > 0.0) {
      const char *t_col = (temp_c < 60.0)
                              ? COLOR_GREEN
                              : ((temp_c < 80.0) ? COLOR_YELLOW : COLOR_RED);
      snprintf(temp_str, sizeof(temp_str), " - %s%.1f°C%s", t_col, temp_c,
               COLOR_WHITE);
    }

    snprintf(buffer, size, "%s%s%s%s", model, core_str, freq_str, temp_str);
  } else {
    strncpy(buffer, "Unknown CPU", size);
  }
}

static void strip_gpu_name(char *s) {
  /* Remove " (rev XX)" suffix */
  char *rev = strstr(s, " (rev ");
  if (rev)
    *rev = '\0';
  /* Remove " Corporation" after vendor if present */
  char *corp = strstr(s, " Corporation");
  if (corp)
    memmove(corp, corp + 12, strlen(corp + 12) + 1);
}

void get_gpu(char *disc_buf, size_t disc_size, char *intg_buf,
             size_t intg_size) {
  /* --- Discrete GPU via nvidia-smi (preferred: clean name + temp) --- */
  disc_buf[0] = '\0';
  FILE *f = popen("nvidia-smi --query-gpu=name,temperature.gpu "
                  "--format=csv,noheader 2>/dev/null",
                  "r");
  if (f) {
    char line[MAX_LINE_LEN];
    if (fgets(line, sizeof(line), f)) {
      trim_newline(line);
      if (line[0] != '\0') {
        /* Format: "Name, Temp" */
        char *comma = strrchr(line, ',');
        if (comma) {
          *comma = '\0';
          trim_newline(line);
          int temp = atoi(comma + 2);
          if (temp > 0) {
            const char *t_col = (temp < 60)
                                    ? COLOR_GREEN
                                    : ((temp < 80) ? COLOR_YELLOW : COLOR_RED);
            snprintf(disc_buf, disc_size, "%s - %s%d.0°C%s [Discrete]", line,
                     t_col, temp, COLOR_WHITE);
          } else
            snprintf(disc_buf, disc_size, "%s [Discrete]", line);
        } else {
          snprintf(disc_buf, disc_size, "%s [Discrete]", line);
        }
      }
    }
    pclose(f);
  }

  /* --- Integrated GPU via lspci --- */
  intg_buf[0] = '\0';
  f = popen("lspci 2>/dev/null | grep -i 'vga\\|3d\\|2d'", "r");
  if (f) {
    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), f)) {
      /* Skip NVIDIA (handled above) */
      if (strcasestr(line, "nvidia") || strcasestr(line, "amd") ||
          strcasestr(line, "radeon"))
        continue;
      char *p = strstr(line, ": ");
      if (p) {
        p += 2;
        trim_newline(p);
        strip_gpu_name(p);
        /* Also strip leading "Intel " duplication if any */
        /* Get Intel iGPU frequency from sysfs */
        double igpu_ghz = 0.0;
        FILE *gf =
            popen("cat /sys/class/drm/card*/gt_boost_freq_mhz "
                  "/sys/class/drm/card*/gt_max_freq_mhz 2>/dev/null | head -1",
                  "r");
        if (gf) {
          long mhz;
          if (fscanf(gf, "%ld", &mhz) == 1 && mhz > 0)
            igpu_ghz = mhz / 1000.0;
          pclose(gf);
        }
        if (igpu_ghz > 0.0)
          snprintf(intg_buf, intg_size, "%s @ %.2f GHz [Integrated]", p,
                   igpu_ghz);
        else
          snprintf(intg_buf, intg_size, "%s [Integrated]", p);
        break;
      }
    }
    pclose(f);
  }

  /* Fallback: if no discrete GPU found via nvidia-smi, try lspci for it */
  if (disc_buf[0] == '\0') {
    f = popen("lspci 2>/dev/null | grep -i 'vga\\|3d\\|2d' | grep -i "
              "'nvidia\\|amd\\|radeon'",
              "r");
    if (f) {
      char line[MAX_LINE_LEN];
      if (fgets(line, sizeof(line), f)) {
        char *p = strstr(line, ": ");
        if (p) {
          p += 2;
          trim_newline(p);
          strip_gpu_name(p);
          snprintf(disc_buf, disc_size, "%s [Discrete]", p);
        }
      }
      pclose(f);
    }
  }
}

void get_disk(char *buffer, size_t size) {
  char fstype[32] = "unknown";
  FILE *f = popen("findmnt -n -o FSTYPE -T / 2>/dev/null", "r");
  if (f) {
    if (fgets(fstype, sizeof(fstype), f))
      trim_newline(fstype);
    pclose(f);
  }

  struct statvfs buf;
  if (statvfs("/", &buf) == 0) {
    double total = (double)buf.f_blocks * buf.f_frsize / (1024 * 1024 * 1024);
    double free = (double)buf.f_bfree * buf.f_frsize / (1024 * 1024 * 1024);
    double used = total - free;
    int pct = (int)((used * 100.0) / total);
    const char *p_col =
        (pct < 50) ? COLOR_GREEN : ((pct < 80) ? COLOR_YELLOW : COLOR_RED);
    snprintf(buffer, size, "%.2f GiB / %.2f GiB (%s%d%%%s) - %s", used, total,
             p_col, pct, COLOR_WHITE, fstype);
  } else {
    strncpy(buffer, "Unknown", size);
  }
}

void get_network(char *buffer, size_t size) {
  /* Get active interface from routing table */
  char iface[32] = "";
  FILE *f = popen("ip -o -4 route get 1.1.1.1 2>/dev/null", "r");
  if (f) {
    char line[512];
    if (fgets(line, sizeof(line), f)) {
      trim_newline(line);
      char *dev = strstr(line, "dev ");
      if (dev) {
        dev += 4;
        char *dev_end = strchr(dev, ' ');
        if (dev_end)
          *dev_end = '\0';
        strncpy(iface, dev, sizeof(iface) - 1);
      }
    }
    pclose(f);
  }
  if (iface[0] == '\0') {
    strncpy(buffer, "Unknown", size);
    return;
  }

  /* Get IP with CIDR prefix length */
  char cmd[128];
  snprintf(cmd, sizeof(cmd), "ip -o -4 addr show dev %s 2>/dev/null", iface);
  f = popen(cmd, "r");
  if (f) {
    char line[512];
    if (fgets(line, sizeof(line), f)) {
      trim_newline(line);
      char *inet = strstr(line, "inet ");
      if (inet) {
        inet += 5;
        char *end = strchr(inet, ' ');
        if (end)
          *end = '\0';
        snprintf(buffer, size, "%s (%s)", inet, iface);
        pclose(f);
        return;
      }
    }
    pclose(f);
  }
  snprintf(buffer, size, "(%s)", iface);
}

void get_desktop(char *buffer, size_t size) {
  char *desk = getenv("XDG_CURRENT_DESKTOP");
  if (!desk)
    desk = getenv("DESKTOP_SESSION");
  if (!desk) {
    strncpy(buffer, "Unknown", size);
    return;
  }

  if (strcasecmp(desk, "KDE") == 0 || strcasecmp(desk, "plasma") == 0) {
    FILE *f = popen("plasmashell --version 2>/dev/null", "r");
    if (f) {
      char line[256];
      if (fgets(line, sizeof(line), f)) {
        trim_newline(line);
        char *p = strchr(line, ' ');
        if (p)
          snprintf(buffer, size, "KDE Plasma %s", p + 1);
        else
          snprintf(buffer, size, "KDE Plasma");
      } else {
        strncpy(buffer, "KDE Plasma", size);
      }
      pclose(f);
    } else {
      strncpy(buffer, "KDE Plasma", size);
    }
  } else {
    strncpy(buffer, desk, size);
  }
}

void get_shell(char *buffer, size_t size) {
  char *sh = getenv("SHELL");
  if (!sh) {
    strncpy(buffer, "Unknown", size);
    return;
  }

  char *sh_name = strrchr(sh, '/');
  if (sh_name)
    sh_name++;
  else
    sh_name = sh;

  char cmd[256];
  snprintf(cmd, sizeof(cmd), "%s --version 2>/dev/null", sh);
  FILE *f = popen(cmd, "r");
  if (f) {
    char line[256];
    if (fgets(line, sizeof(line), f)) {
      trim_newline(line);
      if (strstr(line, "fish, version "))
        snprintf(buffer, size, "fish %s", line + 14);
      else if (strncmp(line, "GNU bash, version ", 18) == 0) {
        char *p = strchr(line + 18, '(');
        if (p)
          *p = '\0';
        trim_newline(line + 18);
        snprintf(buffer, size, "bash %s", line + 18);
      } else if (strncmp(line, "zsh ", 4) == 0)
        snprintf(buffer, size, "%s", line);
      else
        snprintf(buffer, size, "%s", sh_name);
    } else {
      strncpy(buffer, sh_name, size);
    }
    pclose(f);
  } else {
    strncpy(buffer, sh_name, size);
  }
}

void get_term(char *buffer, size_t size) {
  if (getenv("ALACRITTY_WINDOW_ID")) {
    FILE *f = popen("alacritty --version 2>/dev/null", "r");
    if (f) {
      char line[256];
      if (fgets(line, sizeof(line), f)) {
        trim_newline(line);
        /* Strip git hash in parens: "alacritty 0.17.0 (94e7c887)" -> "alacritty
         * 0.17.0" */
        char *paren = strchr(line, '(');
        if (paren && paren > line) {
          *(paren - 1) = '\0'; /* remove space before '(' too */
        }
        strncpy(buffer, line, size - 1);
        buffer[size - 1] = '\0';
      } else {
        strncpy(buffer, "alacritty", size);
      }
      pclose(f);
    } else {
      strncpy(buffer, "alacritty", size);
    }
    return;
  }
  if (getenv("KITTY_WINDOW_ID")) {
    strncpy(buffer, "kitty", size);
    return;
  }
  if (getenv("KONSOLE_VERSION")) {
    strncpy(buffer, "konsole", size);
    return;
  }

  char *term = getenv("TERM_PROGRAM");
  if (!term)
    term = getenv("TERM");
  if (term)
    strncpy(buffer, term, size);
  else
    strncpy(buffer, "Unknown", size);
}

int main() {
  char user[MAX_LINE_LEN] = "user";
  char host[MAX_LINE_LEN] = "hostname";
  char os[MAX_LINE_LEN];
  char kernel[MAX_LINE_LEN];
  char uptime[MAX_LINE_LEN];
  char memory[MAX_LINE_LEN];
  char cpu[MAX_LINE_LEN];
  char gpu1[MAX_LINE_LEN];
  char gpu2[MAX_LINE_LEN];
  char disk[MAX_LINE_LEN];
  char shell[MAX_LINE_LEN];
  char desktop[MAX_LINE_LEN];
  char term[MAX_LINE_LEN];
  char network[MAX_LINE_LEN];

  char *user_env = getenv("USER");
  if (user_env) {
    strncpy(user, user_env, sizeof(user) - 1);
    user[sizeof(user) - 1] = '\0';
  }
  gethostname(host, sizeof(host));

  get_os_name(os, sizeof(os));
  if (getenv("TEST_OS")) {
    strncpy(os, getenv("TEST_OS"), sizeof(os) - 1);
    os[sizeof(os) - 1] = '\0';
  }

  struct utsname buffer;
  if (uname(&buffer) == 0)
    snprintf(kernel, sizeof(kernel), "Linux %s", buffer.release);
  else
    strncpy(kernel, "Unknown", sizeof(kernel));

  get_uptime(uptime, sizeof(uptime));
  get_memory(memory, sizeof(memory));
  get_cpu(cpu, sizeof(cpu));
  get_gpu(gpu1, sizeof(gpu1), gpu2, sizeof(gpu2));
  get_disk(disk, sizeof(disk));
  get_shell(shell, sizeof(shell));
  get_desktop(desktop, sizeof(desktop));
  get_term(term, sizeof(term));
  get_network(network, sizeof(network));

  char *icons[20];
  char *labels[20];
  char *values[20];
  int info_count = 0;

  char os_icon[32];
  if (strcasestr(os, "Arch"))
    strncpy(os_icon, COLOR_CYAN "", sizeof(os_icon));
  else if (strcasestr(os, "Ubuntu"))
    strncpy(os_icon, COLOR_RED "", sizeof(os_icon));
  else if (strcasestr(os, "Debian"))
    strncpy(os_icon, COLOR_RED "", sizeof(os_icon));
  else if (strcasestr(os, "Fedora"))
    strncpy(os_icon, COLOR_BLUE "", sizeof(os_icon));
  else
    strncpy(os_icon, COLOR_CYAN "", sizeof(os_icon));

  icons[info_count] = os_icon;
  labels[info_count] = "distro";
  values[info_count] = os;
  info_count++;
  icons[info_count] = COLOR_CYAN "";
  labels[info_count] = "kernel";
  values[info_count] = kernel;
  info_count++;
  icons[info_count] = COLOR_GREEN "󰅐";
  labels[info_count] = "uptime";
  values[info_count] = uptime;
  info_count++;
  icons[info_count] = COLOR_BLUE "";
  labels[info_count] = "desktop";
  values[info_count] = desktop;
  info_count++;
  icons[info_count] = COLOR_PURPLE "";
  labels[info_count] = "term";
  values[info_count] = term;
  info_count++;
  icons[info_count] = COLOR_CYAN "";
  labels[info_count] = "shell";
  values[info_count] = shell;
  info_count++;
  icons[info_count] = COLOR_BLUE "";
  labels[info_count] = "cpu";
  values[info_count] = cpu;
  info_count++;
  /* Show discrete GPU first, then integrated */
  if (gpu1[0] != '\0') {
    icons[info_count] = COLOR_RED "";
    labels[info_count] = "gpu";
    values[info_count] = gpu1;
    info_count++;
  }
  if (gpu2[0] != '\0') {
    icons[info_count] = COLOR_BLUE "";
    labels[info_count] = "gpu";
    values[info_count] = gpu2;
    info_count++;
  }
  icons[info_count] = COLOR_YELLOW "󰋊";
  labels[info_count] = "disk";
  values[info_count] = disk;
  info_count++;
  icons[info_count] = COLOR_GREEN "󰍛";
  labels[info_count] = "memory";
  values[info_count] = memory;
  info_count++;
  icons[info_count] = COLOR_RED "󰤨";
  labels[info_count] = "network";
  values[info_count] = network;
  info_count++;

  /* Select Logo based on OS */
  const char **ascii_art_ptr = ascii_art_tux;
  int ascii_h = ascii_height_tux;
  int ascii_w = ascii_width_tux;
  const char *ascii_color = COLOR_WHITE;
  if (strcasestr(os, "Arch")) {
    ascii_art_ptr = ascii_art_arch;
    ascii_h = ascii_height_arch;
    ascii_w = ascii_width_arch;
    ascii_color = COLOR_CYAN;
  } else if (strcasestr(os, "Ubuntu")) {
    ascii_art_ptr = ascii_art_ubuntu;
    ascii_h = ascii_height_ubuntu;
    ascii_w = ascii_width_ubuntu;
    ascii_color = COLOR_RED; // Ubuntu orange/red
  } else if (strcasestr(os, "Debian")) {
    ascii_art_ptr = ascii_art_debian;
    ascii_h = ascii_height_debian;
    ascii_w = ascii_width_debian;
    ascii_color = COLOR_RED;
  } else if (strcasestr(os, "Fedora")) {
    ascii_art_ptr = ascii_art_fedora;
    ascii_h = ascii_height_fedora;
    ascii_w = ascii_width_fedora;
    ascii_color = COLOR_BLUE;
  }

  int max_val_len = 0;
  for (int i = 0; i < info_count; i++) {
    int vlen = visible_length(values[i]);
    if (vlen > max_val_len)
      max_val_len = vlen;
  }

  int max_line_len = 0;
  for (int i = 0; i < info_count; i++) {
    char tmp[1024];
    snprintf(tmp, sizeof(tmp), " %s %-7s > %s", icons[i], labels[i], values[i]);
    int len = visible_length(tmp);
    if (len > max_line_len)
      max_line_len = len;
  }

  char title[MAX_LINE_LEN];
  snprintf(title, MAX_LINE_LEN, "%s@%s 💻", user, host);
  int title_len = visible_length(title);

  int inner_width = max_line_len + 4; // Base width from content

  /* title row takes: "═════ " (6) + title_len + " " (1) = title_len + 7.
     We want at least 2 "═" after the title, so title_len + 9 minimum. */
  if (inner_width < title_len + 9) {
    inner_width = title_len + 9;
  }

  int lines_to_print =
      (ascii_h > (info_count + 4)) ? ascii_h : (info_count + 4);

  printf("\n");
  for (int i = 0; i < lines_to_print; i++) {
    if (i < ascii_h)
      printf("%s%-*s%s   ", ascii_color, ascii_w, ascii_art_ptr[i], COLOR_RESET);
    else
      printf("%-*s   ", ascii_w, "");

    if (i == 0) {
      printf("%s╭───── %s%s%s %s", COLOR_GOLD, COLOR_WHITE, title, COLOR_GOLD,
             COLOR_GOLD);
      int rem = inner_width - 6 - title_len - 1;
      for (int j = 0; j < rem; j++)
        printf("─");
      printf("╮%s\n", COLOR_RESET);
    } else if (i <= info_count) {
      int idx = i - 1;
      char inner_str[1024];
      snprintf(inner_str, sizeof(inner_str), " %s %-7s %s> %s%s", icons[idx],
               labels[idx], COLOR_GRAY, COLOR_WHITE, values[idx]);
      int vlen = visible_length(inner_str);
      int padding = inner_width - vlen;
      if (padding < 0)
        padding = 0;

      printf("%s│%s%s%*s%s│%s\n", COLOR_GOLD, COLOR_RESET, inner_str, padding,
             "", COLOR_GOLD, COLOR_RESET);
    } else if (i == info_count + 1) {
      printf("%s├", COLOR_GOLD);
      for (int j = 0; j < inner_width; j++)
        printf("─");
      printf("┤%s\n", COLOR_RESET);
    } else if (i == info_count + 2) {
      char *colors_str = "\x1b[30m● \x1b[31m● \x1b[32m● \x1b[33m● \x1b[34m● "
                         "\x1b[35m● \x1b[36m● \x1b[37m●";
      char inner_str[1024];
      snprintf(inner_str, sizeof(inner_str), "  colors  %s>  %s", COLOR_GRAY,
               colors_str);
      int vlen = visible_length(inner_str);
      int padding = inner_width - vlen;
      if (padding < 0)
        padding = 0;

      printf("%s│%s%s%*s%s│%s\n", COLOR_GOLD, COLOR_RESET, inner_str, padding,
             "", COLOR_GOLD, COLOR_RESET);
    } else if (i == info_count + 3) {
      printf("%s╰", COLOR_GOLD);
      for (int j = 0; j < inner_width; j++)
        printf("─");
      printf("╯%s\n", COLOR_RESET);
    } else {
      printf("\n");
    }
  }
  printf("\n");

  return 0;
}
