'''
    # stepIO Configuration Tool

    stage controller with
    emulation of PIUIO
    by BedrockSolid (@sugoku)

    SPDX-License-Identifier: GPL-3.0-or-later
    https://github.com/sugoku/stepIO
'''


from fbs_runtime.application_context.PyQt5 import ApplicationContext
from PyQt5.QtWidgets import QMainWindow, QDialog
from PyQt5.QtGui import QPixmap
from PyQt5.QtCore import QThreadPool, QRunnable, pyqtSlot
from PyQt5 import uic

import sys
from pathlib import Path
import serial
import serial.tools.list_ports
from stepIO.constants import *
from stepIO.serialc import *

appctxt = ApplicationContext()
device_config = defaults.copy()  # the configuration that is present on the device
working_config = defaults.copy()  # the configuration that is being modified in the tool

def get_com_port_list():
    return [x.device for x in serial.tools.list_ports.comports()]

class AboutWindow(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        uic.loadUi(appctxt.get_resource("ui/about.ui"), self)

        self.setWindowTitle("stepIO - About")
        self.setFixedSize(self.size())

        # set pixmap to logo picture instead of importing a qrc which is redundant
        logo_pixmap = QPixmap(appctxt.get_resource("images/stepiologo256.png"))
        self.logo.setPixmap(logo_pixmap)
        
        # set version
        self.label_ver.setText(f"version {CONFIGTOOL_VERSION}")

class InputsWindow(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        uic.loadUi(appctxt.get_resource("ui/inputs.ui"), self)

        self.sensormenus = [None for i in range(16)]

        self.setWindowTitle("stepIO - Inputs")
        self.setFixedSize(self.size())

        self.input_buttons = [
            self.input_button0,
            self.input_button1,
            self.input_button2,
            self.input_button3,
            self.input_button4,
            self.input_button5,
            self.input_button6,
            self.input_button7,
            self.input_button8,
            self.input_button9,
            self.input_button10,
            self.input_button11,
            self.input_button12,
            self.input_button13,
            self.input_button14,
            self.input_button15
        ]

        # we have to "curry" the functions so that `i` is actually the correct number and not its current value
        func_l = [(lambda x: (lambda: self.inputButtonClicked(x)))(i) for i in range(len(self.input_buttons))]
        for i in range(len(self.input_buttons)):
            self.input_buttons[i].clicked.connect(func_l[i])

    def generateStylesheet(self, inp):
        # border-style, border-color
        inpstat = self.inputs_status[inp]
        return Stylesheet_Inputs.format(
            Stylesheet_Inputs_Enabled if inpstat['enabled'] else Stylesheet_Inputs_Disabled, 
            Stylesheet_Inputs_Width, 
            Stylesheet_Inputs_OnLeft if inpstat['on'][0] else Stylesheet_Inputs_OffLeft, 
            Stylesheet_Inputs_OnDown if inpstat['on'][1] else Stylesheet_Inputs_OffDown, 
            Stylesheet_Inputs_OnUp if inpstat['on'][2] else Stylesheet_Inputs_OffUp, 
            Stylesheet_Inputs_OnRight if inpstat['on'][3] else Stylesheet_Inputs_OffRight, 
            Stylesheet_Inputs_BGColor
        )

    def inputButtonClicked(self, inp):
        if self.sensormenus[inp] is None:
            self.sensormenus[inp] = SensorWindow(self, inp)
        self.sensormenus[inp].inp_setup(inp)
        self.sensormenus[inp].show()

    def updateSensors(self):
        pass



class SensorWindow(QDialog):
    def __init__(self, parent=None, inp=None):
        super().__init__(parent)
        uic.loadUi(appctxt.get_resource("ui/sensor.ui"), self)

        if inp is not None:
            self.inp_setup(inp)

    def inp_setup(self, inp):
        self.inp = inp

        self.setWindowTitle(f"stepIO - Edit Input ({InputPacketNToDisplay[inp]})")
        self.setFixedSize(self.size())

        # below here, add code which populates the proper config for the sensors

        self.comboBox_keyboard.addItems([item for item in KeyboardKeycode])
        # fix this
        self.comboBox_joystick.addItems([item for item in KeyboardKeycode])
        self.comboBox_piuio.addItems([item for item in PIUIO_InputPacketDisplay])

        self.spinBox_analog.setValue(working_config[ConfigOptions[f"{InputPacketStr[inp]}_ANALOG"]])
        self.comboBox_keyboard.setCurrentIndex(working_config[ConfigOptions[f"{InputPacketStr[inp]}_KEYCODE"]])
        self.comboBox_joystick.setCurrentIndex(working_config[ConfigOptions[f"{InputPacketStr[inp]}_GAMEPAD"]])
        # self.comboBox_piuio.setCurrentIndex(working_config[ConfigOptions[f"{InputPacketStr[inp]}_REMAP"]])
        # self.comboBox_piuiobtn.setCurrentIndex(working_config[ConfigOptions[f"{InputPacketStr[inp]}_REMAP"]])
        self.spinBox_midi0.setValue(working_config[ConfigOptions[f"{InputPacketStr[inp]}_MIDI0"]])
        self.spinBox_midi1.setValue(working_config[ConfigOptions[f"{InputPacketStr[inp]}_MIDI1"]])
        self.spinBox_midi2.setValue(working_config[ConfigOptions[f"{InputPacketStr[inp]}_MIDI2"]])

        self.blockedInputs = int.from_bytes(bytes(
            [ConfigOptions[f'BLOCKED_INPUTS_{i}'] for i in range(4)]
        ), byteorder='little')

        self.blockedInputsMux = [int.from_bytes(bytes(
            [ConfigOptions[f'BLOCKED_INPUTS_MUX{mux}_{i}'] for i in range(4)]
        ), byteorder='little') for mux in range(4)]

        self.checkBox_sensorall.setChecked((self.blockedInputs >> inp) & 1)

        self.checkBox_sensor1.setChecked((self.blockedInputsMux[0] >> inp) & 1)
        self.checkBox_sensor2.setChecked((self.blockedInputsMux[1] >> inp) & 1)
        self.checkBox_sensor3.setChecked((self.blockedInputsMux[2] >> inp) & 1)
        self.checkBox_sensor4.setChecked((self.blockedInputsMux[3] >> inp) & 1)

        self.accepted.connect(self.handleSave)
        self.rejected.connect((lambda x: (lambda: self.inp_setup(x)))(inp))  # call this function again when cancelling, resetting the values

    def handleSave(self):
        working_config[ConfigOptions[f"{InputPacketStr[self.inp]}_KEYCODE"]] = self.comboBox_keyboard.currentIndex()
        working_config[ConfigOptions[f"{InputPacketStr[self.inp]}_GAMEPAD"]] = self.comboBox_joystick.currentIndex()
        # working_config[ConfigOptions[f"{InputPacketStr[self.inp]}_REMAP"]] = self.comboBox_piuio.currentIndex()

        working_config[ConfigOptions[f"{InputPacketStr[self.inp]}_ANALOG"]] = self.spinBox_analog.value()

        working_config[ConfigOptions[f"{InputPacketStr[self.inp]}_MIDI0"]] = self.spinBox_midi0.value()
        working_config[ConfigOptions[f"{InputPacketStr[self.inp]}_MIDI1"]] = self.spinBox_midi1.value()
        working_config[ConfigOptions[f"{InputPacketStr[self.inp]}_MIDI2"]] = self.spinBox_midi2.value()
        
        
        self.blockedInputs = SETORCLRBIT(self.blockedInputs, self.inp, self.checkBox_sensorall.isChecked())
        blockedInputs_bytes = self.blockedInputs.to_bytes(4, byteorder='little')
        for i in range(4):
            ConfigOptions[f'BLOCKED_INPUTS_{i}'] = int(blockedInputs_bytes[i])

        self.blockedInputsMux[0] = SETORCLRBIT(self.blockedInputsMux[0], self.inp, self.checkBox_sensor1.isChecked())
        self.blockedInputsMux[1] = SETORCLRBIT(self.blockedInputsMux[1], self.inp, self.checkBox_sensor2.isChecked())
        self.blockedInputsMux[2] = SETORCLRBIT(self.blockedInputsMux[2], self.inp, self.checkBox_sensor3.isChecked())
        self.blockedInputsMux[3] = SETORCLRBIT(self.blockedInputsMux[3], self.inp, self.checkBox_sensor4.isChecked())
        
        for mux in range(len(self.blockedInputsMux)):
            blockedInputsMux_bytes = self.blockedInputsMux[mux].to_bytes(4, byteorder='little')
            for i in range(4):
                ConfigOptions[f'BLOCKED_INPUTS_MUX{mux}_{i}'] = int(blockedInputsMux_bytes[i])

        

class LightsWindow(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        uic.loadUi(appctxt.get_resource("ui/outputs.ui"), self)

        self.parent = parent

        self.setWindowTitle("stepIO - Lights")
        self.setFixedSize(self.size())

        self.comboBox_trigger.addItems([item for item in LightsPacketDisplay]+['None'])  # WARNING: this code is problematic, when making save code check for 'None' separately and set to 0xFF or whatever
        self.comboBox_trigger.setCurrentIndex(working_config[ConfigOptions["EXTRA_LED_TRIGGER"]])
        self.spinBox_count.setValue(working_config[ConfigOptions["RGB_LED_COUNT"]])

        self.lights_buttons = [
            self.pushButton_3,
            self.pushButton_4,
            self.pushButton_5,
            self.pushButton_6,
            self.pushButton_alwayson,
            self.pushButton_marq4,
            self.pushButton_marq1,
            self.pushButton_marq3,
            self.pushButton_marq2,
            self.pushButton_p2dr,
            self.pushButton_p2dl,
            self.pushButton_p2cen,
            self.pushButton_p2ur,
            self.pushButton_p2ul,
            self.pushButton_p2s1,
            self.pushButton_p2s0,
            self.pushButton_19,
            self.pushButton_20,
            self.pushButton_21,
            self.pushButton_22,
            self.pushButton_23,
            self.pushButton_neon,
            self.pushButton_25,
            self.pushButton_26,
            self.pushButton_27,
            self.pushButton_p1dr,
            self.pushButton_p1dl,
            self.pushButton_p1cen,
            self.pushButton_p1ur,
            self.pushButton_p1ul,
            self.pushButton_p1s1,
            self.pushButton_p1s0,
        ]
        self.lights_status = [
            {
                'enabled': True,
                'on': False,
            } for i in range(len(self.lights_buttons))
        ]

        self.LightsPacketToButtons = {
            'P1_UPLEFT': 29,
            'P1_UPRIGHT': 28,
            'P1_CENTER': 27,
            'P1_DOWNLEFT': 26,
            'P1_DOWNRIGHT': 25,
            'P2_UPLEFT': 13,
            'P2_UPRIGHT': 12,
            'P2_CENTER': 11,
            'P2_DOWNLEFT': 10,
            'P2_DOWNRIGHT': 9,
            'MARQUEE_1': 6,
            'MARQUEE_2': 8,
            'MARQUEE_3': 7,
            'MARQUEE_4': 5,
            'SUB_LEFT': 21,
            'SUB_RIGHT': 21,
            'MUX0_S0': 31,
            'MUX0_S1': 30,
            'MUX1_S0': 15,
            'MUX1_S1': 14,
        }
        self.ButtonsToLightsPacket = {v: k for k, v in self.LightsPacketToButtons.items()}

        self.blockedLights = int.from_bytes(bytes(
            [ConfigOptions[f'BLOCKED_LIGHTS_{i}'] for i in range(4)]
        ), byteorder='little')

        func_l = [(lambda x: (lambda: self.toggleLightEnabled(x)))(i) for i in range(len(self.lights_buttons))]
        for light in range(len(self.lights_buttons)):
            bit = LightsPacket.get(self.ButtonsToLightsPacket.get(light))  # qt button index -> lights packet string -> lights packet index
            if bit is not None:
                self.lights_status[light]['enabled'] = bool(GETBIT(self.blockedLights, bit))
            self.lights_buttons[light].clicked.connect(func_l[light])

        self.pushButton_setled.clicked.connect(self.setLED)
        self.pushButton_resetall.clicked.connect(self.resetAllLEDs)

        self.accepted.connect(self.handleSave)
    
    def setLED(self):
        if self.parent.serc is not None:
            pck = SetExtraLEDPacket(self.spinBox_lednum.value(), self.spinBox_r.value(), self.spinBox_g.value(), self.spinBox_b.value())
            self.parent.sendPacketThreaded(pck)

    def resetAllLEDs(self):
        if self.parent.serc is not None:
            pck = ResetExtraLEDsPacket()
            self.parent.sendPacketThreaded(pck)

    def generateStylesheet(self, light):
        # border-style, border-color
        lt = self.lights_status[light]
        return Stylesheet_Lights.format(
            Stylesheet_Lights_Enabled if lt['enabled'] else Stylesheet_Lights_Disabled, 
            Stylesheet_Lights_Width, 
            Stylesheet_Lights_On if lt['on'] else Stylesheet_Lights_Off, 
            Stylesheet_Lights_BGColor
        )

    def updateLights(self):
        if self.parent.serc is not None:
            for i in range(len(self.parent.serc.lights)):
                light = self.LightsPacketToButtons.get(LightsPacketStr.get(i))  # lights packet index -> lights packet string -> qt button index
                if light is not None:
                    self.lights_status[light]['on'] = bool(self.parent.serc.lights[i])
                    self.lights_buttons[light].setStyleSheet(self.generateStyleSheet(light))
            
    def toggleLightEnabled(self, light):  # enabling and disabling lights, not turning them on and off
        self.lights_status[light]['enabled'] = not self.lights_status[light]['enabled']

    def handleSave(self):
        working_config[ConfigOptions["RGB_LED_COUNT"]] = self.spinBox_count.value()
        working_config[ConfigOptions["EXTRA_LED_TRIGGER"]] = self.comboBox_trigger.currentIndex()

        for light in range(len(self.lights_status)):
            bit = LightsPacket.get(self.ButtonsToLightsPacket.get(light))  # qt button index -> lights packet string -> lights packet index
            if bit is not None:
                self.blockedLights = SETORCLRBIT(self.blockedLights, bit, int(self.lights_status[light]['enabled']))
        blockedLights_bytes = self.blockedLights.to_bytes(4, byteorder='little')
        for i in range(4):
            ConfigOptions[f'BLOCKED_LIGHTS_{i}'] = int(blockedLights_bytes[i])
    

class PreferencesWindow(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        uic.loadUi(appctxt.get_resource("ui/preferences.ui"), self)

        self.setWindowTitle("stepIO - Preferences")
        self.setFixedSize(self.size())

    def someSetup(self):
        self.accepted.connect(self.handleSave)
        self.rejected.connect((lambda x: (lambda: self.someSetup(x)))(inp))  # call this function again when cancelling, resetting the values

    def handleSave(self):
        pass

class MainWindow(QMainWindow):
    serc = None

    def __init__(self, parent=None):
        super().__init__(parent)
        uic.loadUi(appctxt.get_resource("ui/main.ui"), self)

        self.pool = QThreadPool()

        self.setWindowTitle("stepIO Configuration Tool")

        self.aboutmenu = None
        self.inputsmenu = None
        self.lightsmenu = None
        self.preferencesmenu = None
        self.resetMenus()

        # disable menu items when a board is not connected
        # self.setBoardItems(False)

        # connection settings
        self.comboBox_baud.addItems(BAUD_LIST_STR)
        self.comboBox_baud.setCurrentIndex(DEFAULT_BAUD_INDEX)
        self.comboBox_com.addItems(get_com_port_list())

        # options
        self.comboBox_outputm.addItems([x for x in OutputModeDisplay])
        self.comboBox_lightsm.addItems([x for x in LightsModeDisplay])

        # advanced options
        self.checkBox_advanced.stateChanged.connect(self.handleCheckAdvancedOptions)

        self.comboBox_extraltm.addItems([x for x in LightsModeDisplay])
        self.comboBox_muxpollm.addItems([x for x in MUXPollingModeDisplay])
        self.comboBox_debouncem.addItems([x for x in DebounceModeDisplay])
        self.comboBox_inputm.addItems([x for x in InputModeDisplay])

    def resetMenus(self):
        if self.aboutmenu is not None:
            self.aboutmenu.close()
        self.aboutmenu = AboutWindow(self)
        self.actionAbout.triggered.connect(self.aboutClicked)

        if self.inputsmenu is not None:
            self.inputsmenu.close()
        self.inputsmenu = InputsWindow(self)
        self.pushButton_editinputs.clicked.connect(self.editInputsClicked)

        if self.lightsmenu is not None:
            self.lightsmenu.close()
        self.lightsmenu = LightsWindow(self)
        self.pushButton_editlights.clicked.connect(self.editLightsClicked)

        if self.preferencesmenu is not None:
            self.preferencesmenu.close()
        self.preferencesmenu = PreferencesWindow(self)
        self.actionPreferences.triggered.connect(self.preferencesClicked)

    def aboutClicked(self):
        self.aboutmenu.show()

    def editInputsClicked(self):
        self.inputsmenu.show()

    def editLightsClicked(self):
        self.lightsmenu.show()
    
    def preferencesClicked(self):
        self.preferencesmenu.show()

    def handleCheckAdvancedOptions(self):
        checked = self.checkBox_advanced.isChecked()
        for box in (self.comboBox_extraltm, self.comboBox_muxpollm, self.comboBox_debouncem, self.comboBox_inputm):
            box.setEnabled(checked)

    def applyToDevice(self):
        pck = SetConfigPacket(working_config)
        self.pushButton_apply.setText("Applying...")
        self.sendPacketThreaded(pck)

    def sendPacketThreaded(self, pck):
        self.pool.start(SendPacketThread(self, pck))

    def applyToDeviceFinished(self):
        self.pushButton_apply.setText("Apply to Device")

    def restoreFactoryDefaults(self):
        restoreBox = QMessageBox()
        restoreBox.setIcon(QMessageBox.Information)
        restoreBox.setWindowTitle("QMessageBox Example")
        restoreBox.setText("Are you sure you want to restore your device to factory defaults? This cannot be undone without a backup of your settings.")
        restoreBox.setStandardButtons(QMessageBox.Yes | QMessageBox.No)

        if restoreBox.exec() == QMessageBox.Yes:
            pck = SetFactoryDefaults()
            self.pushButton_restore.setText("Applying...")
            self.sendPacketThread(pck)
    
    def restoreFactoryDefaultsFinished(self):
        self.pushButton_restore.setText("Restore Factory\nDefaults")

    def undoChanges(self):
        undoBox = QMessageBox()
        undoBox.setIcon(QMessageBox.Information)
        undoBox.setWindowTitle("QMessageBox Example")
        undoBox.setText("Are you sure you want to undo your changes and revert to the device's settings? All changes will be lost and any other windows will be closed.")
        undoBox.setStandardButtons(QMessageBox.Yes | QMessageBox.No)

        if undoBox.exec() == QMessageBox.Yes:
            working_config = device_config.copy()
            self.resetMenus()

    def setBoardItems(self, state):
        self.groupBox_options.setEnabled(state)
        self.groupBox_other.setEnabled(state)
        self.groupBox_applyundo.setEnabled(state)

class SendPacketThread(QRunnable):
    def __init__(self, main_window, pck):
        super(SendPacketThread, self).__init__()
        self.main_window = main_window
        self.pck = pck

    @pyqtSlot()
    def run(self):
        status = self.main_window.serc.sendPacket(pck)
        if status == 1:
            err = QtWidgets.QErrorMessage()
            err.showMessage("A command is currently pending, please wait for it to go through!")
            return
        timer = QTimer(self)
        timer.start(5000)
        while pck.status is not None and timer.isActive():
            pass
        if pck.status == SerialMessages['SUCCESS']:
            self.main_window.label_status.setText("Status: Command Successful")
        elif pck.status is None:
            self.main_window.label_status.setText("Status: Command Timed Out")
        else:
            self.main_window.label_status.setText("Status: Error {pck.status}")

if __name__ == '__main__':
    window = MainWindow()
    window.show()
    exit_code = appctxt.app.exec_()      # 2. Invoke appctxt.app.exec_()
    sys.exit(exit_code)