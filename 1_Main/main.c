/**
 * @file main.c
 * @author 百问网开发团队
 * @brief
 * @version 0.1
 * @date 2022-05-30
 *
 * @copyright Copyright (c) 2022 深圳百问网科技有限公司
 *
 */

#include "drv_led.h"
#include "drv_sysclk.h"
#include "drv_systick.h"
#include "drv_uart.h"
#include "hal_common.h"

#include "tinymaix.h"
#include <stdio.h>

//#define TM_MNIST
//#define TM_CIFAR
#define TM_MBNET
//#define TM_VWW96

#if defined(TM_MNIST)

#include "tmdl/mnist_valid_q.h"

static const uint8_t mnist_pic[28 * 28] = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   116, 125, 171, 255, 255, 150, 93,  0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   169, 253, 253, 253, 253, 253, 253, 218, 30,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   169, 253,
    253, 253, 213, 142, 176, 253, 253, 122, 0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   52,  250, 253, 210, 32,
    12,  0,   6,   206, 253, 140, 0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   77,  251, 210, 25,  0,   0,   0,
    122, 248, 253, 65,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   31,  18,  0,   0,   0,   0,   209, 253,
    253, 65,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   117, 247, 253, 198, 10,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   76,  247, 253, 231, 63,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   128, 253, 253, 144, 0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   176, 246, 253, 159, 12,  0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   25,
    234, 253, 233, 35,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   198, 253, 253,
    141, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   78,  248, 253, 189, 12,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   19,  200, 253, 253, 141, 0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   134, 253, 253, 173, 12,  0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   248, 253, 253, 25,  0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    248, 253, 253, 43,  20,  20,  20,  20,  5,   0,   5,   20,  20,  37,  150,
    150, 150, 147, 10,  0,   0,   0,   0,   0,   0,   0,   0,   0,   248, 253,
    253, 253, 253, 253, 253, 253, 168, 143, 166, 253, 253, 253, 253, 253, 253,
    253, 123, 0,   0,   0,   0,   0,   0,   0,   0,   0,   174, 253, 253, 253,
    253, 253, 253, 253, 253, 253, 253, 253, 249, 247, 247, 169, 117, 117, 57,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   118, 123, 123, 123, 166,
    253, 253, 253, 155, 123, 123, 41,  0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,
};

static tm_err_t layer_cb(tm_mdl_t *mdl, tml_head_t *lh) { // dump middle result
  int h = lh->out_dims[1];
  int w = lh->out_dims[2];
  int ch = lh->out_dims[3];
  mtype_t *output = TML_GET_OUTPUT(mdl, lh);
  return TM_OK;
  TM_PRINTF("Layer %d callback ========\n", mdl->layer_i);
#if 1
  for (int y = 0; y < h; y++) {
    TM_PRINTF("[");
    for (int x = 0; x < w; x++) {
      TM_PRINTF("[");
      for (int c = 0; c < ch; c++) {
#if TM_MDL_TYPE == TM_MDL_FP32
        TM_PRINTF("%.3f,", output[(y * w + x) * ch + c]);
#else
        TM_PRINTF("%.3f,", TML_DEQUANT(lh, output[(y * w + x) * ch + c]));
#endif
      }
      TM_PRINTF("],");
    }
    TM_PRINTF("],\n");
  }
  TM_PRINTF("\n");
#endif
  return TM_OK;
}

static void parse_output(tm_mat_t *outs) {
  tm_mat_t out = outs[0];
  float *data = out.dataf;
  float maxp = 0;
  int maxi = -1;
  for (int i = 0; i < 10; i++) {
    printf("%d: %.3f\n", i, data[i]);
    if (data[i] > maxp) {
      maxi = i;
      maxp = data[i];
    }
  }
  TM_PRINTF("### Predict output is: Number %d, prob %.3f\n", maxi, maxp);
  return;
}

#elif defined(TM_CIFAR)

#include "cipic2.h"
#include "tmdl/cifar10_q.h"

#define IMG_L 32
#define IMG_CH 3
#define CLASS_NUM 10

char *labels[CLASS_NUM] = {"airplane", "automobile", "bird",  "cat",  "deer",
                           "dog",      "frog",       "hrose", "ship", "truck"};

static tm_err_t layer_cb(tm_mdl_t *mdl, tml_head_t *lh) { // dump middle result
  int h = lh->out_dims[1];
  int w = lh->out_dims[2];
  int ch = lh->out_dims[3];
  mtype_t *output = TML_GET_OUTPUT(mdl, lh);
  return TM_OK;
  TM_PRINTF("Layer %d callback ========\n", mdl->layer_i);
#if 1
  for (int y = 0; y < h; y++) {
    TM_PRINTF("[");
    for (int x = 0; x < w; x++) {
      TM_PRINTF("[");
      for (int c = 0; c < ch; c++) {
#if TM_MDL_TYPE == TM_MDL_FP32
        TM_PRINTF("%.3f,", output[(y * w + x) * ch + c]);
#else
        TM_PRINTF("%.3f,", TML_DEQUANT(lh, output[(y * w + x) * ch + c]));
#endif
      }
      TM_PRINTF("],");
    }
    TM_PRINTF("],\n");
  }
  TM_PRINTF("\n");
#endif
  return TM_OK;
}

static void parse_output(tm_mat_t *outs) {
  tm_mat_t out = outs[0];
  float *data = out.dataf;
  float maxp = 0;
  int maxi = -1;
  for (int i = 0; i < CLASS_NUM; i++) {
    printf("%d: %.3f\n", i, data[i]);
    if (data[i] > maxp) {
      maxi = i;
      maxp = data[i];
    }
  }
  TM_PRINTF("### Predict output is: Class %d, %s, prob %.3f\n", maxi,
            labels[maxi], maxp);
  return;
}

#elif defined(TM_MBNET)

#include "tmdl/mbnet96_0.25_q.h"
#include "pic128.h"

#define IMG_L 96

const char *labels[1] = {
    "tench, Tinca tinca",
};

static tm_err_t layer_cb(tm_mdl_t *mdl, tml_head_t *lh) { // dump middle result
  int h = lh->out_dims[1];
  int w = lh->out_dims[2];
  int ch = lh->out_dims[3];
  mtype_t *output = TML_GET_OUTPUT(mdl, lh);
  return TM_OK;
}

static void parse_output(tm_mat_t *outs) {
  tm_mat_t out = outs[0];
  float *data = out.dataf;
  float maxp = 0;
  int maxi = -1;
  for (int i = 0; i < 1000; i++) {
    if (data[i] > maxp) {
      maxi = i;
      maxp = data[i];
    }
  }
  TM_PRINTF("### Predict output is: Class %d (%s), Prob %.3f\n", maxi,
            labels[maxi], maxp);
  return;
}

#elif defined(TM_VWW96)

#include "pic_person1.h"
#include "tmdl/vww96_q.h"

#define IMG_L 96
#define IMG_CH 3
#define CLASS_NUM 2

char *labels[CLASS_NUM] = {"no-person", "person"};

static tm_err_t layer_cb(tm_mdl_t *mdl, tml_head_t *lh) { // dump middle result
  int h = lh->out_dims[1];
  int w = lh->out_dims[2];
  int ch = lh->out_dims[3];
  mtype_t *output = TML_GET_OUTPUT(mdl, lh);
  return TM_OK;
  TM_PRINTF("Layer %d callback ========\n", mdl->layer_i);
  return TM_OK;
}

static void parse_output(tm_mat_t *outs) {
  tm_mat_t out = outs[0];
  float *data = out.dataf;
  float maxp = 0;
  int maxi = -1;
  for (int i = 0; i < CLASS_NUM; i++) {
    printf("%d: %.3f\n", i, data[i]);
    if (data[i] > maxp) {
      maxi = i;
      maxp = data[i];
    }
  }
  TM_PRINTF("### Predict output is: Class %d, %s, prob %.3f\n", maxi,
            labels[maxi], maxp);
  return;
}

#endif

static uint8_t mdl_buf[MDL_BUF_LEN];

/**
 * @brief ARM处理器程序入口函数
 *
 * @return int 通常main函数不会有返回值
 */
int main(void) {
  /* 定义LED的状态变量，按键按下时取反 */
  LED_Status status = off;
  /* 初始化系统时钟频率为120MHz */
  SystemClockConfig();
  /* 配置滴答定时器的技术周期是1kHz */
  Drv_SysTick_Config();
  /* 初始化用户LED的GPIO和默认状态 */
  Drv_LED_Init();
  /* 初始化串口 */
  Drv_UART_Init();

#if defined(TM_MNIST)
  TM_DBGT_INIT();
  TM_PRINTF("mnist demo\n");
  tm_mdl_t mdl;

  for (int i = 0; i < 28 * 28; i++) {
    TM_PRINTF("%3d,", mnist_pic[i]);
    if (i % 28 == 27)
      TM_PRINTF("\n");
  }

  tm_mat_t in_uint8 = {3, 28, 28, 1, {(mtype_t *)mnist_pic}};
  tm_mat_t in = {3, 28, 28, 1, {NULL}};
  tm_mat_t outs[1];
  tm_err_t res;
  tm_stat((tm_mdlbin_t *)mdl_data);

  res = tm_load(&mdl, mdl_data, mdl_buf, layer_cb, &in);
  if (res != TM_OK) {
    TM_PRINTF("tm model load err %d\n", res);
    return -1;
  }

#if (TM_MDL_TYPE == TM_MDL_INT8) || (TM_MDL_TYPE == TM_MDL_INT16)
  res = tm_preprocess(&mdl, TMPP_UINT2INT, &in_uint8, &in);
#else
  res = tm_preprocess(&mdl, TMPP_UINT2FP01, &in_uint8, &in);
#endif
  TM_DBGT_START();
  res = tm_run(&mdl, &in, outs);
  TM_DBGT("tm_run");
  if (res == TM_OK)
    parse_output(outs);
  else
    TM_PRINTF("tm run error: %d\n", res);
  tm_unload(&mdl);

#elif defined(TM_CIFAR)
  TM_DBGT_INIT();
  TM_PRINTF("cifar10 demo\n");
  tm_mdl_t mdl;

  tm_mat_t in_uint8 = {3, IMG_L, IMG_L, IMG_CH, {(mtype_t *)pic}};
  tm_mat_t in = {3, IMG_L, IMG_L, IMG_CH, {NULL}};
  tm_mat_t outs[1];
  tm_err_t res;
  tm_stat((tm_mdlbin_t *)mdl_data);

  res = tm_load(&mdl, mdl_data, mdl_buf, layer_cb, &in);
  if (res != TM_OK) {
    TM_PRINTF("tm model load err %d\n", res);
    return -1;
  }

#if (TM_MDL_TYPE == TM_MDL_INT8) || (TM_MDL_TYPE == TM_MDL_INT16)
  res = tm_preprocess(&mdl, TMPP_UINT2INT, &in_uint8, &in);
#else
  res = tm_preprocess(&mdl, TMPP_UINT2FP01, &in_uint8, &in);
#endif
  TM_DBGT_START();
  res = tm_run(&mdl, &in, outs);
  TM_DBGT("tm_run");
  if (res == TM_OK)
    parse_output(outs);
  else
    TM_PRINTF("tm run error: %d\n", res);
  tm_unload(&mdl);

#elif defined(TM_MBNET)

  TM_DBGT_INIT();
  TM_PRINTF("mbnet demo\n");
  tm_mdl_t mdl;

  tm_mat_t in_uint8 = {3, IMG_L, IMG_L, 3, {(mtype_t *)pic}};
  tm_mat_t in = {3, IMG_L, IMG_L, 3, {NULL}};
  tm_mat_t outs[1];
  tm_err_t res;
  tm_stat((tm_mdlbin_t *)mdl_data);

  res = tm_load(&mdl, mdl_data, mdl_buf, layer_cb, &in);
  if (res != TM_OK) {
    TM_PRINTF("tm model load err %d\n", res);
    return -1;
  }
#if (TM_MDL_TYPE == TM_MDL_INT8) || (TM_MDL_TYPE == TM_MDL_INT16)
  res = tm_preprocess(&mdl, TMPP_UINT2INT, &in_uint8, &in);
#else
  res = tm_preprocess(&mdl, TMPP_UINT2FP01, &in_uint8, &in);
#endif
  TM_DBGT_START();
  res = tm_run(&mdl, &in, outs);
  TM_DBGT("tm_run");
  if (res != TM_OK)
    TM_PRINTF("tm run error: %d\n", res);
  tm_unload(&mdl);

#elif defined(TM_VWW96)
  TM_DBGT_INIT();
  TM_PRINTF("mnist demo\n");
  tm_mdl_t mdl;

  tm_mat_t in_uint8 = {3, IMG_L, IMG_L, IMG_CH, {(mtype_t *)pic}};
  tm_mat_t in = {3, IMG_L, IMG_L, IMG_CH, {NULL}};
  tm_mat_t outs[1];
  tm_err_t res;
  tm_stat((tm_mdlbin_t *)mdl_data);

  res = tm_load(&mdl, mdl_data, mdl_buf, layer_cb, &in);
  if (res != TM_OK) {
    TM_PRINTF("tm model load err %d\n", res);
    return -1;
  }

#if (TM_MDL_TYPE == TM_MDL_INT8) || (TM_MDL_TYPE == TM_MDL_INT16)
  res = tm_preprocess(&mdl, TMPP_UINT2INT, &in_uint8, &in);
#else
  res = tm_preprocess(&mdl, TMPP_UINT2FP01, &in_uint8, &in);
#endif
  TM_DBGT_START();
  res = tm_run(&mdl, &in, outs);
  TM_DBGT("tm_run");
  if (res == TM_OK)
    parse_output(outs);
  else
    TM_PRINTF("tm run error: %d\n", res);
  tm_unload(&mdl);

#endif

  while (1) {
    /* TDO Your Task */
    status = !status;
    Drv_LED_Write(user_led, status); // 控制LED
    printf("LED状态:%s\r\n", (status == on) ? "on" : "off");
    HAL_Delay(500);
  }
}
