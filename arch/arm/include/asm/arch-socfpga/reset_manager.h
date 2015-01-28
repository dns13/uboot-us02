/*
 *  Copyright (C) 2012 Altera Corporation <www.altera.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef	_RESET_MANAGER_H_
#define	_RESET_MANAGER_H_

#ifndef __ASSEMBLY__
void watchdog_disable(void);
int is_wdt_in_reset(void);
void reset_cpu(ulong addr);
void reset_deassert_all_peripherals(void);
void reset_deassert_all_bridges(void);
void reset_deassert_cpu1(void);
void reset_deassert_osc1timer0(void);
void reset_deassert_osc1wd0(void);
void reset_assert_all_peripherals(void);
void reset_assert_all_peripherals_except_l4wd0(void);
void reset_assert_all_bridges(void);
#ifdef CONFIG_SPL_BUILD
void reset_deassert_peripherals_handoff(void);
void reset_deassert_bridges_handoff(void);
#endif
void emac0_reset_enable(uint state);
void emac1_reset_enable(uint state);
void reset_clock_manager(void);
extern unsigned reset_clock_manager_size;

#if defined(CONFIG_SOCFPGA_VIRTUAL_TARGET)
struct socfpga_reset_manager {
	u32	padding1;
	u32	ctrl;
	u32	padding2;
	u32	padding3;
	u32	mpu_mod_reset;
	u32	per_mod_reset;
};
#else
struct socfpga_reset_manager {
	u32	status;
	u32	ctrl;
	u32	counts;
	u32	padding1;
	u32	mpu_mod_reset;
	u32	per_mod_reset;
	u32	per2_mod_reset;
	u32	brg_mod_reset;
};
#endif
#endif /* __ASSEMBLY__ */

#if defined(CONFIG_SOCFPGA_VIRTUAL_TARGET)
#define RSTMGR_CTRL_SWWARMRSTREQ_LSB 2
#define RSTMGR_PERMODRST_OSC1TIMER0_LSB 10
#else
#define RSTMGR_CTRL_SWWARMRSTREQ_LSB 1
#define RSTMGR_PERMODRST_OSC1TIMER0_LSB 8
#endif

#define RSTMGR_PERMODRST_EMAC0_LSB 0
#define RSTMGR_PERMODRST_EMAC1_LSB 1
#define RSTMGR_PERMODRST_L4WD0_LSB 6
#define RSTMGR_PERMODRST_SDR_LSB 29
#define RSTMGR_BRGMODRST_HPS2FPGA_MASK		0x00000001
#define RSTMGR_BRGMODRST_LWHPS2FPGA_MASK	0x00000002
#define RSTMGR_BRGMODRST_FPGA2HPS_MASK		0x00000004

#define RSTMGR_CTRL_OFFSET			0x00000004
#define RSTMGR_MISCMODRST_OFFSET		0x00000020
#define RSTMGR_MISCMODRST_CLKMGRCOLD_MASK	0x00000400

/* Warm Reset mask */
#if defined(CONFIG_SOCFPGA_VIRTUAL_TARGET)
#define RESET_MANAGER_REGS_STATUS_REG_L4_WD1_RST_FLD_MASK 0x00008000
#define RESET_MANAGER_REGS_STATUS_REG_L4_WD0_RST_FLD_MASK 0x00004000
#define RESET_MANAGER_REGS_STATUS_REG_MPU_WD1_RST_FLD_MASK 0x00002000
#define RESET_MANAGER_REGS_STATUS_REG_MPU_WD0_RST_FLD_MASK 0x00001000
#define RESET_MANAGER_REGS_STATUS_REG_SW_WARM_RST_FLD_MASK 0x00000400
#define RESET_MANAGER_REGS_STATUS_REG_FPGA_WARM_RST_FLD_MASK 0x00000200
#define RESET_MANAGER_REGS_STATUS_REG_NRST_FLD_MASK 0x00000100
#define RSTMGR_WARMRST_MASK	(\
	RESET_MANAGER_REGS_STATUS_REG_L4_WD1_RST_FLD_MASK | \
	RESET_MANAGER_REGS_STATUS_REG_L4_WD0_RST_FLD_MASK | \
	RESET_MANAGER_REGS_STATUS_REG_MPU_WD1_RST_FLD_MASK | \
	RESET_MANAGER_REGS_STATUS_REG_MPU_WD0_RST_FLD_MASK | \
	RESET_MANAGER_REGS_STATUS_REG_SW_WARM_RST_FLD_MASK | \
	RESET_MANAGER_REGS_STATUS_REG_FPGA_WARM_RST_FLD_MASK | \
	RESET_MANAGER_REGS_STATUS_REG_NRST_FLD_MASK)
#define RSTMGR_CTRL_SDRSELFREFEN_MASK 0x00000008
#define RSTMGR_CTRL_FPGAHSEN_MASK 0x00000000	/* not available in VT */
#define RSTMGR_CTRL_ETRSTALLEN_MASK 0x00000010
#else
#define RSTMGR_STAT_L4WD1RST_MASK 0x00008000
#define RSTMGR_STAT_L4WD0RST_MASK 0x00004000
#define RSTMGR_STAT_MPUWD1RST_MASK 0x00002000
#define RSTMGR_STAT_MPUWD0RST_MASK 0x00001000
#define RSTMGR_STAT_SWWARMRST_MASK 0x00000400
#define RSTMGR_STAT_FPGAWARMRST_MASK 0x00000200
#define RSTMGR_STAT_NRSTPINRST_MASK 0x00000100
#define RSTMGR_WARMRST_MASK	(\
	RSTMGR_STAT_L4WD1RST_MASK | \
	RSTMGR_STAT_L4WD0RST_MASK | \
	RSTMGR_STAT_MPUWD1RST_MASK | \
	RSTMGR_STAT_MPUWD0RST_MASK | \
	RSTMGR_STAT_SWWARMRST_MASK | \
	RSTMGR_STAT_FPGAWARMRST_MASK | \
	RSTMGR_STAT_NRSTPINRST_MASK)
#define RSTMGR_CTRL_SDRSELFREFEN_MASK 0x00000010
#define RSTMGR_CTRL_FPGAHSEN_MASK 0x00010000
#define RSTMGR_CTRL_ETRSTALLEN_MASK 0x00100000
#endif

#if defined(CONFIG_SOCFPGA_VIRTUAL_TARGET)

#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_EMAC0_RST_FLD_SET(x) \
(((x) << 0) & 0x00000001)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_EMAC1_RST_FLD_SET(x) \
(((x) << 1) & 0x00000002)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_USB0_RST_FLD_SET(x) \
(((x) << 2) & 0x00000004)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_USB1_RST_FLD_SET(x) \
(((x) << 3) & 0x00000008)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_NAND_FLASH_RST_FLD_SET(x) \
(((x) << 4) & 0x00000010)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_QSPI_FLASH_RST_FLD_SET(x) \
(((x) << 5) & 0x00000020)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_WATCHDOG0_RST_FLD_SET(x) \
(((x) << 6) & 0x00000040)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_WATCHDOG1_RST_FLD_SET(x) \
(((x) << 7) & 0x00000080)

#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_OSC1_TIMER0_RST_FLD_SET(x) \
(((x) << 10) & 0x00000400)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_OSC1_TIMER1_RST_FLD_SET(x) \
(((x) << 11) & 0x00000800)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_SP_TIMER0_RST_FLD_SET(x) \
(((x) << 8) & 0x00000100)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_SP_TIMER1_RST_FLD_SET(x) \
(((x) << 9) & 0x00000200)

#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_I2C0_RST_FLD_SET(x) \
(((x) << 12) & 0x00001000)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_I2C1_RST_FLD_SET(x) \
(((x) << 13) & 0x00002000)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_I2C2_RST_FLD_SET(x) \
(((x) << 14) & 0x00004000)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_I2C3_RST_FLD_SET(x) \
(((x) << 15) & 0x00008000)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_UART0_RST_FLD_SET(x) \
(((x) << 16) & 0x00010000)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_UART1_RST_FLD_SET(x) \
(((x) << 17) & 0x00020000)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_SPI_RST_FLD_SET(x) \
(((x) << 18) & 0x00040000)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_SDMMC_RST_FLD_SET(x) \
(((x) << 19) & 0x00080000)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_CAN0_RST_FLD_SET(x) \
(((x) << 20) & 0x00100000)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_CAN1_RST_FLD_SET(x) \
(((x) << 21) & 0x00200000)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_GPIO0_RST_FLD_SET(x) \
(((x) << 22) & 0x00400000)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_GPIO1_RST_FLD_SET(x) \
(((x) << 23) & 0x00800000)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_GPIO2_RST_FLD_SET(x) \
(((x) << 24) & 0x01000000)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_DMA_RST_FLD_SET(x) \
(((x) << 25) & 0x02000000)
#define RESET_MANAGER_REGS_PERIPH_MODULE_RST_REG_SDRAM_RST_FLD_SET(x) \
(((x) << 26) & 0x04000000)


#else

#define RSTMGR_PERMODRST_EMAC0_SET(x) \
(((x) << 0) & 0x00000001)
#define RSTMGR_PERMODRST_EMAC1_SET(x) \
(((x) << 1) & 0x00000002)
#define RSTMGR_PERMODRST_USB0_SET(x) \
(((x) << 2) & 0x00000004)
#define RSTMGR_PERMODRST_USB1_SET(x) \
(((x) << 3) & 0x00000008)
#define RSTMGR_PERMODRST_NAND_SET(x) \
(((x) << 4) & 0x00000010)
#define RSTMGR_PERMODRST_QSPI_SET(x) \
(((x) << 5) & 0x00000020)
#define RSTMGR_PERMODRST_L4WD1_SET(x) \
(((x) << 7) & 0x00000080)
#define RSTMGR_PERMODRST_OSC1TIMER1_SET(x) \
(((x) << 9) & 0x00000200)
#define RSTMGR_PERMODRST_SPTIMER0_SET(x) \
(((x) << 10) & 0x00000400)
#define RSTMGR_PERMODRST_SPTIMER1_SET(x) \
(((x) << 11) & 0x00000800)
#define RSTMGR_PERMODRST_I2C0_SET(x) \
(((x) << 12) & 0x00001000)
#define RSTMGR_PERMODRST_I2C1_SET(x) \
(((x) << 13) & 0x00002000)
#define RSTMGR_PERMODRST_I2C2_SET(x) \
(((x) << 14) & 0x00004000)
#define RSTMGR_PERMODRST_I2C3_SET(x) \
(((x) << 15) & 0x00008000)
#define RSTMGR_PERMODRST_UART0_SET(x) \
(((x) << 16) & 0x00010000)
#define RSTMGR_PERMODRST_UART1_SET(x) \
(((x) << 17) & 0x00020000)
#define RSTMGR_PERMODRST_SPIM0_SET(x) \
(((x) << 18) & 0x00040000)
#define RSTMGR_PERMODRST_SPIM1_SET(x) \
(((x) << 19) & 0x00080000)
#define RSTMGR_PERMODRST_SPIS0_SET(x) \
(((x) << 20) & 0x00100000)
#define RSTMGR_PERMODRST_SPIS1_SET(x) \
(((x) << 21) & 0x00200000)
#define RSTMGR_PERMODRST_SDMMC_SET(x) \
(((x) << 22) & 0x00400000)
#define RSTMGR_PERMODRST_CAN0_SET(x) \
(((x) << 23) & 0x00800000)
#define RSTMGR_PERMODRST_CAN1_SET(x) \
(((x) << 24) & 0x01000000)
#define RSTMGR_PERMODRST_GPIO0_SET(x) \
(((x) << 25) & 0x02000000)
#define RSTMGR_PERMODRST_GPIO1_SET(x) \
(((x) << 26) & 0x04000000)
#define RSTMGR_PERMODRST_GPIO2_SET(x) \
(((x) << 27) & 0x08000000)
#define RSTMGR_PERMODRST_DMA_SET(x) \
(((x) << 28) & 0x10000000)
#define RSTMGR_PERMODRST_SDR_SET(x) \
(((x) << 29) & 0x20000000)

#define RSTMGR_PER2MODRST_DMAIF0_SET(x) \
(((x) << 0) & 0x00000001)
#define RSTMGR_PER2MODRST_DMAIF1_SET(x) \
(((x) << 1) & 0x00000002)
#define RSTMGR_PER2MODRST_DMAIF2_SET(x) \
(((x) << 2) & 0x00000004)
#define RSTMGR_PER2MODRST_DMAIF3_SET(x) \
(((x) << 3) & 0x00000008)
#define RSTMGR_PER2MODRST_DMAIF4_SET(x) \
(((x) << 4) & 0x00000010)
#define RSTMGR_PER2MODRST_DMAIF5_SET(x) \
(((x) << 5) & 0x00000020)
#define RSTMGR_PER2MODRST_DMAIF6_SET(x) \
(((x) << 6) & 0x00000040)
#define RSTMGR_PER2MODRST_DMAIF7_SET(x) \
(((x) << 7) & 0x00000080)

#endif

#endif /* _RESET_MANAGER_H_ */

