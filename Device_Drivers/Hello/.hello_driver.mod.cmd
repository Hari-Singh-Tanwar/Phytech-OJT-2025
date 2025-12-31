savedcmd_hello_driver.mod := printf '%s\n'   hello_driver.o | awk '!x[$$0]++ { print("./"$$0) }' > hello_driver.mod
