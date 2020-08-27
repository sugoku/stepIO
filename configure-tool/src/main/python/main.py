from fbs_runtime.application_context.PyQt5 import ApplicationContext
from PyQt5.QtWidgets import QMainWindow, QDialog
from PyQt5.QtGui import QPixmap
from PyQt5 import uic

import sys
import serial
import serial.tools.list_ports
from constants import *

appctxt = ApplicationContext()
ser = serial.Serial()

def get_com_port_list():
    return [x.device for x in serial.tools.list_ports.comports()]

class AboutWindow(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        uic.loadUi(appctxt.get_resource("ui/about.ui"), self)

        self.setWindowTitle("About stepIO")
        self.setFixedSize(self.size())

        # set pixmap to logo picture instead of importing a qrc which is redundant
        logo_pixmap = QPixmap(appctxt.get_resource("images/stepiologo256.png"))
        self.logo.setPixmap(logo_pixmap)

class InputsWindow(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        uic.loadUi(appctxt.get_resource("ui/inputs.ui"), self)

        self.setWindowTitle("stepIO Inputs")
        self.setFixedSize(self.size())

class LightsWindow(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        uic.loadUi(appctxt.get_resource("ui/outputs.ui"), self)

        self.setWindowTitle("stepIO Lights")
        self.setFixedSize(self.size())

class PreferencesWindow(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        uic.loadUi(appctxt.get_resource("ui/preferences.ui"), self)

        self.setWindowTitle("stepIO Preferences")
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