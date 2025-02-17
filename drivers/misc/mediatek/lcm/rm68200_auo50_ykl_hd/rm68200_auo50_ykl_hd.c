#ifndef BUILD_LK
#include <linux/string.h>
#endif
#include "lcm_drv.h"

#ifdef BUILD_LK
#include <platform/mt_gpio.h>
#include <platform/mt_pmic.h>
#elif defined(BUILD_UBOOT)
#include <asm/arch/mt_gpio.h>
#else
#include <mt-plat/mt_gpio.h>
//#include <mt-plat/upmu_common.h>
#include <linux/string.h>
#include <linux/kernel.h>
#endif
#include "lcm_drv.h"

// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH   (720) // (480)
#define FRAME_HEIGHT  (1280) // (854)


#define REGFLAG_DELAY             							0XFEE
#define REGFLAG_END_OF_TABLE      							0xFFF   // END OF REGISTERS MARKER

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE 
#define TRUE 1
#endif
//static unsigned int lcm_esd_test = FALSE;      ///only for ESD test
#define LCM_DSI_CMD_MODE									0

#define LCM_RM68200_ID 		(0x6820)

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = { 0 };

#define SET_RESET_PIN(v)    		(lcm_util.set_reset_pin((v)))

#define UDELAY(n) 			(lcm_util.udelay(n))
#define MDELAY(n) 			(lcm_util.mdelay(n))


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update) lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update) lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)									lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums) lcm_util.dsi_write_regs(addr, pdata, byte_nums)
/* #define read_reg lcm_util.dsi_read_reg() */
#define read_reg_v2(cmd, buffer, buffer_size) lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)


struct LCM_setting_table {
  unsigned cmd;
  unsigned char count;
  unsigned char para_list[64];
};

static void lcm_init_power(void)
{
}


static void lcm_suspend_power(void)
{
}

static void lcm_resume_power(void)
{
}
static struct LCM_setting_table lcm_initialization_setting[] = {
  {0xFE, 1,{0x01}},

{0x24, 1,{0x00}},

  {0x25, 1,{0x53}},

  {0x26, 1,{0x00}},

{0x27, 1,{0x0A}},

{0x29, 1,{0x0A}},

  {0x2B, 1,{0xE5}},

  {0x16, 1,{0x52}},

{0x2F, 1,{0x54}},

  {0x34, 1,{0x59}},

{0x1B, 1,{0x50}},

{0x12, 1,{0x02}},

  {0x1A, 1,{0x06}},

{0x46, 1,{0x5F}},

{0x52, 1,{0x70}},
{0x53, 1,{0x00}},

{0x54, 1,{0x70}},

{0x55, 1,{0x00}}, //0D

{0x5F, 1,{0x13}},

{0xFE, 1,{0x03}},

{0x00, 1,{0x05}},

{0x01, 1,{0x16}},

{0x02, 1,{0x0B}},

{0x03, 1,{0x0F}},

{0x04, 1,{0x7D}},

{0x05, 1,{0x00}},

{0x06, 1,{0x50}},

{0x07, 1,{0x05}},

{0x08, 1,{0x16}},

{0x09, 1,{0x0D}},

{0x0A, 1,{0x11}},

{0x0B, 1,{0x7D}},

{0x0C, 1,{0x00}},

{0x0D, 1,{0x50}},

{0x0E, 1,{0x07}},

{0x0F, 1,{0x08}},

{0x10, 1,{0x01}},

{0x11, 1,{0x02}},

{0x12, 1,{0x00}},

{0x13, 1,{0x7D}},

{0x14, 1,{0x00}},

{0x15, 1,{0x85}},

{0x16, 1,{0x08}},

{0x17, 1,{0x03}},

{0x18, 1,{0x04}},

{0x19, 1,{0x05}},

{0x1A, 1,{0x06}},

{0x1B, 1,{0x00}},

{0x1C, 1,{0x7D}},

{0x1D, 1,{0x00}},

{0x1E, 1,{0x85}},

{0x1F, 1,{0x08}},

{0x20, 1,{0x00}},

{0x21, 1,{0x00}},

{0x22, 1,{0x00}},

{0x23, 1,{0x00}},

{0x24, 1,{0x00}},

{0x25, 1,{0x00}},

{0x26, 1,{0x00}},

{0x27, 1,{0x00}},

{0x28, 1,{0x00}},

{0x29, 1,{0x00}},

{0x2A, 1,{0x07}},

{0x2B, 1,{0x08}},

{0x2D, 1,{0x01}},

{0x2F, 1,{0x02}},

{0x30, 1,{0x00}},

{0x31, 1,{0x40}},

{0x32, 1,{0x05}},

{0x33, 1,{0x08}},

{0x34, 1,{0x54}},

{0x35, 1,{0x7D}},

{0x36, 1,{0x00}},

{0x37, 1,{0x03}},

{0x38, 1,{0x04}},

{0x39, 1,{0x05}},

{0x3A, 1,{0x06}},

{0x3B, 1,{0x00}},

{0x3D, 1,{0x40}},

{0x3F, 1,{0x05}},

{0x40, 1,{0x08}},

{0x41, 1,{0x54}},

{0x42, 1,{0x7D}},

{0x43, 1,{0x00}},

{0x44, 1,{0x00}},

{0x45, 1,{0x00}},

{0x46, 1,{0x00}},

{0x47, 1,{0x00}},

{0x48, 1,{0x00}},

{0x49, 1,{0x00}},

{0x4A, 1,{0x00}},

{0x4B, 1,{0x00}},

{0x4C, 1,{0x00}},

{0x4D, 1,{0x00}},

{0x4E, 1,{0x00}},

{0x4F, 1,{0x00}},

{0x50, 1,{0x00}},

{0x51, 1,{0x00}},

{0x52, 1,{0x00}},

{0x53, 1,{0x00}},

{0x54, 1,{0x00}},

{0x55, 1,{0x00}},

{0x56, 1,{0x00}},

{0x58, 1,{0x00}},

{0x59, 1,{0x00}},

{0x5A, 1,{0x00}},

{0x5B, 1,{0x00}},

{0x5C, 1,{0x00}},

{0x5D, 1,{0x00}},

{0x5E, 1,{0x00}},

{0x5F, 1,{0x00}},

{0x60, 1,{0x00}},

{0x61, 1,{0x00}},

{0x62, 1,{0x00}},

{0x63, 1,{0x00}},

{0x64, 1,{0x00}},

{0x65, 1,{0x00}},

{0x66, 1,{0x00}},

{0x67, 1,{0x00}},

{0x68, 1,{0x00}},

{0x69, 1,{0x00}},

{0x6A, 1,{0x00}},

{0x6B, 1,{0x00}},

{0x6C, 1,{0x00}},

{0x6D, 1,{0x00}},

{0x6E, 1,{0x00}},

{0x6F, 1,{0x00}},

{0x70, 1,{0x00}},

{0x71, 1,{0x00}},

{0x72, 1,{0x20}},

{0x73, 1,{0x00}},

{0x74, 1,{0x08}},

{0x75, 1,{0x08}},

{0x76, 1,{0x08}},

{0x77, 1,{0x08}},

{0x78, 1,{0x08}},

{0x79, 1,{0x08}},

{0x7A, 1,{0x00}},

{0x7B, 1,{0x00}},

{0x7C, 1,{0x00}},

{0x7D, 1,{0x00}},

{0x7E, 1,{0xBF}},

{0x7F, 1,{0x3F}},

{0x80, 1,{0x3F}},

{0x81, 1,{0x3F}},

{0x82, 1,{0x3F}},

{0x83, 1,{0x3F}},

{0x84, 1,{0x3F}},

{0x85, 1,{0x02}},

{0x86, 1,{0x06}},

{0x87, 1,{0x3F}},

{0x88, 1,{0x14}},

{0x89, 1,{0x10}},

{0x8A, 1,{0x16}},

{0x8B, 1,{0x12}},

{0x8C, 1,{0x08}},

{0x8D, 1,{0x0C}},

{0x8E, 1,{0x0A}},

{0x8F, 1,{0x0E}},

{0x90, 1,{0x00}},

{0x91, 1,{0x04}},

{0x92, 1,{0x3F}},

{0x93, 1,{0x3F}},

{0x94, 1,{0x3F}},

{0x95, 1,{0x3F}},

{0x96, 1,{0x05}},

{0x97, 1,{0x01}},

{0x98, 1,{0x0F}},

{0x99, 1,{0x0B}},

{0x9A, 1,{0x0D}},

{0x9B, 1,{0x09}},

{0x9C, 1,{0x13}},

{0x9D, 1,{0x17}},

{0x9E, 1,{0x11}},

{0x9F, 1,{0x15}},

{0xA0, 1,{0x3F}},

{0xA2, 1,{0x07}},

{0xA3, 1,{0x03}},

{0xA4, 1,{0x3F}},

{0xA5, 1,{0x3F}},

{0xA6, 1,{0x3F}},

{0xA7, 1,{0x3F}},

{0xA9, 1,{0x3F}},

{0xAA, 1,{0x3F}},

{0xAB, 1,{0x3F}},

{0xAC, 1,{0x3F}},

{0xAD, 1,{0x3F}},

{0xAE, 1,{0x3F}},

{0xAF, 1,{0x3F}},

{0xB0, 1,{0x3F}},

{0xB1, 1,{0x3F}},

{0xB2, 1,{0x3F}},

{0xB3, 1,{0x05}},

{0xB4, 1,{0x01}},

{0xB5, 1,{0x3F}},

{0xB6, 1,{0x17}},

{0xB7, 1,{0x13}},

{0xB8, 1,{0x15}},

{0xB9, 1,{0x11}},

{0xBA, 1,{0x0F}},

{0xBB, 1,{0x0B}},

{0xBC, 1,{0x0D}},

{0xBD, 1,{0x09}},

{0xBE, 1,{0x07}},

{0xBF, 1,{0x03}},

{0xC0, 1,{0x3F}},

{0xC1, 1,{0x3F}},

{0xC2, 1,{0x3F}},

{0xC3, 1,{0x3F}},

{0xC4, 1,{0x02}},

{0xC5, 1,{0x06}},

{0xC6, 1,{0x08}},

{0xC7, 1,{0x0C}},

{0xC8, 1,{0x0A}},

{0xC9, 1,{0x0E}},

{0xCA, 1,{0x10}},

{0xCB, 1,{0x14}},

{0xCC, 1,{0x12}},

{0xCD, 1,{0x16}},

{0xCE, 1,{0x3F}},

{0xCF, 1,{0x00}},

{0xD0, 1,{0x04}},

{0xD1, 1,{0x3F}},

{0xD2, 1,{0x3F}},

{0xD3, 1,{0x3F}},

{0xD4, 1,{0x3F}},

{0xD5, 1,{0x3F}},

{0xD6, 1,{0x3F}},

{0xD7, 1,{0x3F}},

{0xDC, 1,{0x02}},

{0xDE, 1,{0x12}},


{0xFE, 1,{0x0E}},

{0x01, 1,{0x75}},


{0xFE, 1,{0x04}},

{0x60, 1,{0x00}},//0A

{0x61, 1,{0x08}},

{0x62, 1,{0x0E}},

{0x63, 1,{0x0D}},

{0x64, 1,{0x05}},

{0x65, 1,{0x10}},

{0x66, 1,{0x0E}},

{0x67, 1,{0x0A}},

{0x68, 1,{0x16}},

{0x69, 1,{0x0C}},

{0x6A, 1,{0x10}},

{0x6B, 1,{0x07}},

{0x6C, 1,{0x0E}},

{0x6D, 1,{0x13}},

{0x6E, 1,{0x0C}},

{0x6F, 1,{0x00}},//03

{0x70, 1,{0x00}},

{0x71, 1,{0x08}},

{0x72, 1,{0x0E}},

{0x73, 1,{0x0D}},

{0x74, 1,{0x05}},

{0x75, 1,{0x10}},

{0x76, 1,{0x0E}},

{0x77, 1,{0x0A}},

{0x78, 1,{0x16}},

{0x79, 1,{0x0C}},

{0x7A, 1,{0x10}},

{0x7B, 1,{0x07}},

{0x7C, 1,{0x0E}},

{0x7D, 1,{0x13}},

{0x7E, 1,{0x0C}},

{0x7F, 1,{0x00}},


{0xFE, 1,{0x00}},

  {0x11, 1,{0x00}},
  {REGFLAG_DELAY, 120, {}},
  {0x29, 1,{0x00}},
  {REGFLAG_DELAY, 50, {}},

  {REGFLAG_END_OF_TABLE, 0x00, {}}
};

static void push_table(struct LCM_setting_table *table, unsigned int count,
    unsigned char force_update)
{
  unsigned int i;

  for (i = 0; i < count; i++) {

    unsigned cmd;
    cmd = table[i].cmd;

    switch (cmd) {

      case REGFLAG_DELAY:
        MDELAY(table[i].count);
        break;

      case REGFLAG_END_OF_TABLE:
        break;

      default:
        dsi_set_cmdq_V2(cmd, table[i].count,
            table[i].para_list, force_update);
    }
  }

}
// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS * util)
{
  memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}

static void lcm_get_params(LCM_PARAMS * params)
{
  memset(params, 0, sizeof(LCM_PARAMS));

  params->type = LCM_TYPE_DSI;

  params->width = FRAME_WIDTH;
  params->height = FRAME_HEIGHT;

  // enable tearing-free
  params->dbi.te_mode = LCM_DBI_TE_MODE_DISABLED;
  params->dbi.te_edge_polarity = LCM_POLARITY_RISING;

#if (LCM_DSI_CMD_MODE)
  params->dsi.mode = CMD_MODE;
#else
  params->dsi.mode   = SYNC_PULSE_VDO_MODE;//SYNC_EVENT_VDO_MODE;//BURST_VDO_MODE;////
#endif

  // DSI
  /* Command mode setting */
  params->dsi.LANE_NUM				= LCM_FOUR_LANE;//LCM_FOUR_LANE;

  //The following defined the fomat for data coming from LCD engine.
  params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
  params->dsi.data_format.trans_seq   = LCM_DSI_TRANS_SEQ_MSB_FIRST;
  params->dsi.data_format.padding     = LCM_DSI_PADDING_ON_LSB;
  params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;


  params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;
#if (LCM_DSI_CMD_MODE)
  params->dsi.intermediat_buffer_num = 0;//because DSI/DPI HW design change, this parameters should be 0 when video mode in MT658X; or memory leakage
  params->dsi.word_count=FRAME_WIDTH*3;	//DSI CMD mode need set these two bellow params, different to 6577
#else
  params->dsi.intermediat_buffer_num = 0;	//because DSI/DPI HW design change, this parameters should be 0 when video mode in MT658X; or memory leakage
#endif

  // Video mode setting
  params->dsi.packet_size=256;

  params->dsi.vertical_sync_active                = 2;// 3    2
  params->dsi.vertical_backporch                  = 14;// 20   1
  params->dsi.vertical_frontporch                 = 16; // 1  12
  params->dsi.vertical_active_line				= FRAME_HEIGHT; 

  params->dsi.horizontal_sync_active              = 8;// 50  2
  params->dsi.horizontal_backporch                = 64;//90
  params->dsi.horizontal_frontporch               = 64;//90
  params->dsi.horizontal_active_pixel				= FRAME_WIDTH;

  params->dsi.PLL_CLOCK =210;
  // Bit rate calculation

#ifdef VANZO_LCM_ESD_CHECK_SUPPORT
  params->dsi.noncont_clock = TRUE;
  params->dsi.noncont_clock_period =1;

  params->dsi.esd_check_enable = 1;
  params->dsi.customization_esd_check_enable = 1;
  params->dsi.lcm_esd_check_table[0].cmd          = 0x0a;
  params->dsi.lcm_esd_check_table[0].count        = 1;
  params->dsi.lcm_esd_check_table[0].para_list[0] = 0x9C;
#endif
}

static void lcm_init(void)
{
  SET_RESET_PIN(1);
  MDELAY(10);
  SET_RESET_PIN(0);
  MDELAY(50);
  SET_RESET_PIN(1);
  MDELAY(120);

  push_table(lcm_initialization_setting,sizeof(lcm_initialization_setting) /sizeof(struct LCM_setting_table), 1);
}

static void lcm_suspend(void)
{
  unsigned int data_array[16];

  data_array[0] = 0x00280500;
  dsi_set_cmdq(data_array, 1, 1);
  MDELAY(10);

  data_array[0] = 0x00100500;
  dsi_set_cmdq(data_array, 1, 1);
  MDELAY(150);
  SET_RESET_PIN(0);
  MDELAY(120);
}
static void lcm_resume(void)
{
  lcm_init();
}


static unsigned int lcm_compare_id(void)
{
  unsigned int id, id_high,id_low;
  unsigned char buffer[5];
  unsigned int array[5];
  SET_RESET_PIN(1);
  MDELAY(10);
  SET_RESET_PIN(0);
  MDELAY(10);
  SET_RESET_PIN(1);
  MDELAY(100);
  /*
     push_table(lcm_compare_id_setting,
     sizeof(lcm_compare_id_setting) /
     sizeof(struct LCM_setting_table), 1);
   */
  array[0]=0x01FE1500;
  dsi_set_cmdq(&array,1, 1);

  array[0] = 0x00013700;
  dsi_set_cmdq(array, 1, 1);
  read_reg_v2(0xde, buffer, 1);

  id_high = buffer[0];
  read_reg_v2(0xdf, buffer, 1);
  id_low = buffer[0];
  id = (id_high<<8) | id_low;
#if defined(BUILD_LK)
  printf("%s, [rm68200_auo55]  buffer[0] = [0x%d] buffer[2] = [0x%d] ID = [0x%d]\n",__func__, buffer[0], buffer[1], id);
#else
  printk("%s, [rm68200_auo55]  buffer[0] = [0x%d] buffer[2] = [0x%d] ID = [0x%d]\n",__func__, buffer[0], buffer[1], id);
#endif

  return ((LCM_RM68200_ID == id)? 1 : 0);
}

LCM_DRIVER rm68200_auo50_ykl_hd_lcm_drv =
{
  .name			= "rm68200_auo50_ykl_hd",
  .set_util_funcs = lcm_set_util_funcs,
  .get_params = lcm_get_params,
  .init = lcm_init,
  .suspend = lcm_suspend,
  .resume = lcm_resume,
  .compare_id = lcm_compare_id,
  .init_power        = lcm_init_power,
  .resume_power = lcm_resume_power,
  .suspend_power = lcm_suspend_power,
};
