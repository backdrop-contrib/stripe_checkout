#Stripe Checkout

This module enables the creation of a simple donation block
which you can place in layouts on your Backdrop site. It is a very simple
implementation using Stripe's [Checkout](https://stripe.com/docs/checkout) 
functionality and does not create local database tables for storing or 
browsing donation history. You can use your Stripe account to view and 
manage that. 

Even though Stripe handles all the payment info on their servers, you 
should still ensure your site is running on SSL. ("All submissions of payment 
info using Checkout are made via a secure HTTPS connection. However, in order 
to protect yourself from certain forms of man-in-the-middle attacks, you must 
serve the page containing the payment form over HTTPS as well. In short, the 
address of the page containing Checkout must start with https:// rather than 
just http://.")

Features may be expanded in the future.

##Dependencies

- Currently requires the Libraries module
- [Stripe's PHP bindings](https://github.com/stripe/stripe-php) should be 
  copied into the `/libraries` directory in a folder named `stripe_php`.

##Installation

- Once the dependencies are in place, install this module using the [official 
  Backdrop CMS instructions](https://backdropcms.org/guide/modules).
- Configure the module at *Configuration > Web Services > Stripe >  
  Checkout Settings* (`admin/config/services/stripe_api/checkout`).
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
- Co-maintainers would be welcome!

##Credits

- This module was created by [Laryn Kragt Bakker](https://github.com/laryn) - 
[CEDC.org](https://cedc.org).