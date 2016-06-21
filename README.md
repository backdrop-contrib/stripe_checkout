#Stripe Checkout

This module enables the creation of a simple donation block
which you can place in layouts on your Backdrop site. It is a very simple
implementation using Stripe's "Checkout" functionality and does not create
local database tables for storing or browsing donation history. You can
use your Stripe account to view and manage that. 

Features may be expanded in the future.

##Dependencies

- Currently requires the Libraries module
- [Stripe's PHP bindings](https://github.com/stripe/stripe-php) should be 
  copied into the `/libraries` directory in a folder named `stripe_php`.

##Installation

- Once the dependencies are in place, install this module using the [official 
  Backdrop CMS instructions](https://backdropcms.org/guide/modules).
- Configure the module at *Configuration > Web Services > Stripe Checkout*
  (`admin/config/services/stripe-checkout`), adding your Stripe API keys and 
  setting preferences.
- Add the "Stripe Checkout Donation" block 
  [to a layout](https://backdropcms.org/guide/layouts) and adjust visibility 
  settings as needed.

![Stripe Checkout](https://github.com/backdrop-contrib/stripe_checkout/blob/1.x-1.x/images/stripe_checkout-screenshot.jpg "Stripe Checkout screenshot")

##Issues

Bugs and Feature requests should be reported in this module's 
[Issue Queue](https://github.com/backdrop-contrib/stripe_checkout/issues).

##License

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.

##Current Maintainers

- [Laryn Kragt Bakker](https://github.com/laryn) - [CEDC.org](https://cedc.org)

##Credits

- This module was created by [Laryn Kragt Bakker](https://github.com/laryn) - 
[CEDC.org](https://cedc.org).