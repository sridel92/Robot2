// simple motor command by enabled D10 D11 D12
/* to NANO, motor commands
 * D12=0    D11=0   D10=0   Stop
 * D12=1    D11=1   D10=1   Forward
 * D12=1    D11=1   D10=0   Left
 * D12=1    D11=0   D10=1   Right
 * D12=1    D11=0   D10=0   Backward
 */

void MotorStop() {   // Stop
      digitalWrite(D10, LOW);
      digitalWrite(D11, LOW);
      digitalWrite(D12, LOW);
      }

void MotorFwd() {   // Forward
      digitalWrite(D10, HIGH);
      digitalWrite(D11, HIGH);
      digitalWrite(D12, HIGH);
      }

void MotorRev() {   // Backward
      digitalWrite(D10, LOW);
      digitalWrite(D11, LOW);
      digitalWrite(D12, HIGH);
      }

void MotorLeft() {   // Left
      digitalWrite(D10, LOW);
      digitalWrite(D11, HIGH);
      digitalWrite(D12, HIGH);
      }

void MotorRight() {   // Right
      digitalWrite(D10, HIGH);
      digitalWrite(D11, LOW);
      digitalWrite(D12, HIGH);
      }


