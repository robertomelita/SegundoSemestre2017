var=$(xinput | grep 'Gaming Mouse')
echo Configurando con id=${var:50:1}
$(xinput set-prop "${var:50:1}" "Device Accel Constant Deceleration" 2.5)
echo Configurando con id=${var:50:2}
$(xinput set-prop "${var:50:2}" "Device Accel Constant Deceleration" 2.5)
