(function($) {

  /**
   * Scrolls to top of Webform with Stripe payment.
   */
  Backdrop.ajax.prototype.commands.stripeCheckoutWebformScroll = function(ajax, response, status) {
    // Determine what to scroll to, either our wrapper div, or a block, or a
    // Panels pane.
    var $el = $(response.selector).closest('.block.block-webform');
    if (!$el.length) {
      $el = $(response.selector).closest('.panel-pane.pane-block[class*="pane-webform-client-block-"');
      if (!$el.length) {
        $el = $(response.selector);
      }
    }

    // Get element top, and offset it if Adminimal Menu is in use.
    var top = $el.offset().top;
    if ($('body').hasClass('adminimal-menu')) {
      top -= 29;
    }

    // Scroll!
    $('html, body').animate({scrollTop: top}, response.duration);
  };

  /**
   * Opens Stripe Checkout when Webform Stripe 'pay' button is clicked.
   */
  Backdrop.behaviors.stripeCheckoutWebform = {
    attach: function(context, settings) {
      $('.stripe-checkout-webform-pay', context).click(function() {
        StripeCheckout.open($.extend(settings.stripe_checkout_webform, {
          // Payment was successful.
          token: function(token) {
            // Set token and email in token field.
            $('.stripe-checkout-webform-token', context).val(token.id + ':' + token.email);

            // Submit form.
            $('.webform-submit', context).click();
          }
        }));
        return false;
      });
    }
  };

}(jQuery));
