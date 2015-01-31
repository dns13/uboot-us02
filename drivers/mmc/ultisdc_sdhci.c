/*
 * sdhci-ultimmc.c Support for SDHCI UltiMMC cora on Altera FPGA.
 *
 * Author: Giovanni Pavoni Exor s.p.a.
 */

#include <common.h>
#include <malloc.h>
#include <sdhci.h>

/*
 * Implementation of the I/O accessor functions.
 * 
 * NOTE: We need to use our custom accessor functions (CONFIG_MMC_SDHCI_IO_ACCESSOR is defined)
 * since the register offsets are 4 bits shifted to the left
 */  

static u32 sdhci_ultimmc_readl(struct sdhci_host *host, int reg)
{
  u32 ret;
  reg = reg << 4; //Register map has offsets right shifted of 4 bits
  ret = readl(host->ioaddr + reg);
  return ret;
}

static u16 sdhci_ultimmc_readw(struct sdhci_host *host, int reg)
{
  u16 ret;
  reg = reg << 4; //Register map has offsets right shifted of 4 bits
  ret = readw(host->ioaddr + reg);
  return ret;
}

static u8 sdhci_ultimmc_readb(struct sdhci_host *host, int reg)
{
  u8 ret;
  reg = reg << 4; //Register map has offsets right shifted of 4 bits
  ret = readb(host->ioaddr + reg);
  return ret;
}

static void sdhci_ultimmc_writel(struct sdhci_host *host, u32 val, int reg)
{
  reg = reg << 4; //Register map has offsets right shifted of 4 bits
  writel(val, host->ioaddr + reg);
}

static void sdhci_ultimmc_writew(struct sdhci_host *host, u16 val, int reg)
{
  if(reg == SDHCI_CLOCK_CONTROL)
  {
    // Force <50Mhz clock
    if(((val >> SDHCI_DIVIDER_SHIFT) & SDHCI_DIV_MASK) < 0x01)
    {
      val |= (0x01 & SDHCI_DIV_MASK) << SDHCI_DIVIDER_SHIFT;
    }
  }
  reg = reg << 4; //Register map has offsets right shifted of 4 bits
  writew(val, host->ioaddr + reg);
}

static void sdhci_ultimmc_writeb(struct sdhci_host *host, u8 val, int reg)
{
  reg = reg << 4; //Register map has offsets right shifted of 4 bits
  writeb(val, host->ioaddr + reg);
}

static struct sdhci_ops sdhci_ultimmc_ops = {
	.read_b	= sdhci_ultimmc_readb,
	.read_w	= sdhci_ultimmc_readw,
	.read_l	= sdhci_ultimmc_readl,
	.write_b= sdhci_ultimmc_writeb,
	.write_w= sdhci_ultimmc_writew,
	.write_l= sdhci_ultimmc_writel,
};

static char *CORE_NAME = "ultisdc";
int ultisdc_init(u32 regbase, int index)
{
	struct sdhci_host *host = NULL;
	host = (struct sdhci_host *)malloc(sizeof(struct sdhci_host));
	if (!host) {
		printf("sdh_host malloc fail!\n");
		return 1;
	}

	host->name = CORE_NAME;
	host->ioaddr = (void *)regbase;
	host->quirks = SDHCI_QUIRK_NO_SIMULT_VDD_AND_POWER |
		  SDHCI_QUIRK_NO_HISPD_BIT ;
//		  SDHCI_QUIRK_BROKEN_TIMEOUT_VAL |
//		  SDHCI_QUIRK_BROKEN_DMA |   
//		  SDHCI_QUIRK_DELAY_AFTER_POWER |
//		  SDHCI_QUIRK_NO_MULTIBLOCK | 
//		  SDHCI_QUIRK_BROKEN_ADMA;

	host->ops = &sdhci_ultimmc_ops;
	host->index = index;
	add_sdhci(host, 50000000, 400000);
	return 0;
}
