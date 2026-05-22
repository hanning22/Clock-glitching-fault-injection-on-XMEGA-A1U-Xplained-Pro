```mermaid
flowchart LR
    subgraph CWL["ChipWhisperer Lite"]
        CW_GND["Pin 2: GND"]
        CW_RST["Pin 5: nRST Reset"]
        CW_CLK["Pin 6: HS2 Clock Output"]
        CW_RX["Pin 10: TIO1 UART Rx"]
        CW_TX["Pin 12: TIO2 UART Tx"]
        CW_TRIG["Pin 16: TIO4 Trigger"]
    end

    subgraph XMEGA["XMEGA Xplained Pro"]
        XP_GND["J100 Pin 2: GND"]
        XP_RST["TP300 Reset"]
        XP_CLK["EXT1 Pin 10: PR1 GPIO / External Clock"]
        XP_TX["EXT1 Pin 14: PC3 UART Tx"]
        XP_RX["EXT1 Pin 13: PC2 UART Rx"]
        XP_TRIG["EXT1 Pin 3: PA0 ADC0 Trigger"]
    end

    CW_GND --- XP_GND
    CW_RST --> XP_RST
    CW_CLK --> XP_CLK
    CW_RX --> XP_TX
    CW_TX --> XP_RX
    CW_TRIG --> XP_TRIG
