from fbs_runtime.application_context.PyQt5 import ApplicationContext
from PyQt5.QtWidgets import QMainWindow, QDialog
from PyQt5.QtGui import QPixmap
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


    def inputButtonClicked(self, inp):
        if self.sensormenus[inp] is None:
            self.sensormenus[inp] = SensorWindow(self, inp)
        self.sensormenus[inp].show()



class SensorWindow(QDialog):
    def __init__(self, parent=None, inp=None):
        super().__init__(parent)
        uic.loadUi(appctxt.get_resource("ui/sensor.ui"), self)

        if inp is not None:
            self.inp_setup(inp)

    def inp_setup(self, inp):
        self.inp = inp

        self.setWindowTitle(f"stepIO - Edit Input {inp}")
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
        

class LightsWindow(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        uic.loadUi(appctxt.get_resource("ui/outputs.ui"), self)

        self.setWindowTitle("stepIO - Lights")
        self.setFixedSize(self.size())

class PreferencesWindow(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        uic.loadUi(appctxt.get_resource("ui/preferences.ui"), self)

        self.setWindowTitle("stepIO - Preferences")
        self.setFixedSize(self.size())

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)
        uic.loadUi(appctxt.get_resource("ui/main.ui"), self)

        self.setWindowTitle("stepIO Configuration Tool")

        # prepare menus
        self.aboutmenu = AboutWindow(self)
        self.actionAbout.triggered.connect(self.aboutClicked)

        self.inputsmenu = InputsWindow(self)
        self.pushButton_editinputs.clicked.connect(self.editInputsClicked)

        self.lightsmenu = LightsWindow(self)
        self.pushButton_editlights.clicked.connect(self.editLightsClicked)

        self.preferencesmenu = PreferencesWindow(self)
        self.actionPreferences.triggered.connect(self.preferencesClicked)

        # disable menu items when a board is not connected
        # self.disableDisconnectedItems()

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

    def disableDisconnectedItems(self):
        self.groupBox_options.setEnabled(False)
        self.groupBox_other.setEnabled(False)
        self.groupBox_applyundo.setEnabled(False)


if __name__ == '__main__':
    window = MainWindow()
    window.show()
    exit_code = appctxt.app.exec_()      # 2. Invoke appctxt.app.exec_()
    sys.exit(exit_code)