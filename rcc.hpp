#pragma once

#include "periph.hpp"

namespace stm32f7::rcc {

enum class gpioa     { disable, enable, mask = 1 << 0 };  // Bit 0 GPIOAEN: IO port A clock enable
enum class gpiob     { disable, enable, mask = 1 << 1 };  // Bit 1 GPIOBEN: IO port B clock enable
enum class gpioc     { disable, enable, mask = 1 << 2 };  // Bit 2 GPIOCEN: IO port C clock enable
enum class gpiod     { disable, enable, mask = 1 << 3 };  // Bit 3 GPIODEN: IO port D clock enable
enum class gpioe     { disable, enable, mask = 1 << 4 };  // Bit 4 GPIOEEN: IO port E clock enable
enum class gpiof     { disable, enable, mask = 1 << 5 };  // Bit 5 GPIOFEN: IO port F clock enable
enum class gpiog     { disable, enable, mask = 1 << 6 };  // Bit 6 GPIOGEN: IO port G clock enable
enum class gpioh     { disable, enable, mask = 1 << 7 };  // Bit 7 GPIOHEN: IO port H clock enable
enum class gpioi     { disable, enable, mask = 1 << 8 };  // Bit 8 GPIOIEN: IO port I clock enable
enum class gpioj     { disable, enable, mask = 1 << 9 };  // Bit 9 GPIOJEN: IO port J clock enable
enum class gpiok     { disable, enable, mask = 1 << 10 }; // Bit 10 GPIOKEN: IO port K clock enable
enum class crc       { disable, enable, mask = 1 << 12 }; // Bit 12 CRCEN: CRC clock enable
enum class bkpsram   { disable, enable, mask = 1 << 18 }; // Bit 18 BKPSRAMEN: Backup SRAM interface clock enable
enum class dtcmram   { disable, enable, mask = 1 << 20 }; // Bit 20 DTCMRAMEN: DTCM data RAM clock enable
enum class dma1      { disable, enable, mask = 1 << 21 }; // Bit 21 DMA1EN: DMA1 clock enable
enum class dma2      { disable, enable, mask = 1 << 22 }; // Bit 22 DMA2EN: DMA2 clock enable
enum class dma2d     { disable, enable, mask = 1 << 23 }; // Bit 23 DMA2DEN: DMA2D clock enable
enum class ethmac    { disable, enable, mask = 1 << 25 }; // Bit 25 ETHMACEN: Ethernet MAC clock enable
enum class ethmactx  { disable, enable, mask = 1 << 26 }; // Bit 26 ETHMACTXEN: Ethernet Transmission clock enable
enum class ethmacrx  { disable, enable, mask = 1 << 27 }; // Bit 27 ETHMACRXEN: Ethernet Reception clock enable
enum class ethmaptp  { disable, enable, mask = 1 << 28 }; // Bit 28 ETHMACPTPEN: Ethernet PTP clock enable
enum class otghs     { disable, enable, mask = 1 << 29 }; // Bit 29 OTGHSEN: USB OTG HS clock enable
enum class otghsulpi { disable, enable, mask = 1 << 30 }; // Bit 30 OTGHSULPIEN: USB OTG HSULPI clock enable

} // namespace stm32f7::gpio {

namespace stm32f7::rcc::registers {

struct ahb1enr {
    static constexpr std::size_t offset = 0x30;
    static constexpr auto params = type_pack<
          gpioa, gpiob, gpioc, gpiod, gpioe, gpiof, gpiog, gpioh, gpioi, gpioj, gpiok
        , crc
        , bkpsram
        , dtcmram
        , dma1, dma2, dma2d
        , ethmac, ethmactx, ethmacrx, ethmaptp
        , otghs, otghsulpi
    >{};
};

} // namespace stm32f7::gpio::registers


namespace stm32f7 {

template<class meta>
struct RCC_t final : periph<
      meta
    , rcc::registers::ahb1enr
>{};

struct RCC_meta { static constexpr std::size_t address = 0x4002'3800; };

using RCC = RCC_t<RCC_meta>;

} // namespace stm32f7 {


